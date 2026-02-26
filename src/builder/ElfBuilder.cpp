#include "elfparser/builder/ElfBuilder.h"
#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Builder {

    ElfBuilder::ElfBuilder(const std::string& outputPath)
        : m_outputPath(outputPath) {

        // Ensure index 0 is reserved for SHT_NULL
        m_sections.push_back(nullptr);

        // Create .shstrtab
        auto shstrtab = std::make_unique<Components::StringTableBuilder>(".shstrtab");
        m_shstrtabRef = shstrtab.get();
        AddSection(std::move(shstrtab));
    }

    Components::EhdrBuilder& ElfBuilder::GetHeaderBuilder() {
        return m_ehdrBuilder;
    }

    Components::PhdrBuilder& ElfBuilder::GetProgramHeaderBuilder() {
        return m_phdrBuilder;
    }

    Components::ShdrBuilder& ElfBuilder::GetSectionHeaderBuilder() {
        return m_shdrBuilder;
    }

    void ElfBuilder::AddSection(std::unique_ptr<Components::SectionBuilder> section) {
        if (!section) return;

        // Add section name to .shstrtab
        // Note: For .shstrtab itself, this works because we set m_shstrtabRef before calling AddSection
        if (m_shstrtabRef) {
            uint32_t nameIdx = m_shstrtabRef->AddString(section->GetName());
            section->GetHeader().sh_name = nameIdx;
        }

        m_sections.push_back(std::move(section));
    }

    void ElfBuilder::RemoveSection(const std::string& name) {
        for (auto it = m_sections.begin(); it != m_sections.end(); ++it) {
            if (*it && (*it)->GetName() == name) {
                // If we remove .shstrtab, we must clear the reference
                if (it->get() == m_shstrtabRef) {
                    m_shstrtabRef = nullptr;
                }
                m_sections.erase(it);
                return;
            }
        }
    }

    Components::SectionBuilder* ElfBuilder::GetSection(const std::string& name) {
        for (const auto& section : m_sections) {
            if (section && section->GetName() == name) {
                return section.get();
            }
        }
        return nullptr;
    }

    Components::StringTableBuilder& ElfBuilder::GetSectionHeaderStringTable() {
        return *m_shstrtabRef;
    }

    Common::Result ElfBuilder::Build() {
        IO::BinaryWriter writer(m_outputPath);
        auto res = writer.Open();
        if (!res.IsOk()) return res;

        // 1. Prepare Layout
        Layout::LayoutManager layout(0);

        // Elf Header
        layout.Advance(sizeof(Model::Elf64_Ehdr));

        // Program Headers
        uint64_t phoff = layout.GetCurrentOffset();
        if (m_phdrBuilder.GetCount() > 0) {
            layout.Advance(m_phdrBuilder.GetSize());
        } else {
            phoff = 0;
        }

        // Sections
        // We need to update each section's header with offset and size
        for (size_t i = 1; i < m_sections.size(); ++i) {
            auto& section = m_sections[i];

            // Align
            uint64_t align = section->GetHeader().sh_addralign;
            layout.Align(align);

            uint64_t offset = layout.GetCurrentOffset();
            uint64_t size = section->GetSize();

            section->UpdateHeader(offset, size);
            layout.Advance(size);
        }

        // Section Headers
        // Align for section headers (usually 8 bytes for 64-bit)
        layout.Align(8);
        uint64_t shoff = layout.GetCurrentOffset();

        // 2. Finalize Elf Header
        // Find shstrtab index
        uint16_t shstrndx = 0;
        for (size_t i = 0; i < m_sections.size(); ++i) {
            if (m_sections[i].get() == m_shstrtabRef) {
                shstrndx = static_cast<uint16_t>(i);
                break;
            }
        }

        m_ehdrBuilder.UpdateLayout(
            phoff,
            m_phdrBuilder.GetCount(),
            shoff,
            static_cast<uint16_t>(m_sections.size()), // shnum includes NULL section
            shstrndx
        );

        // 3. Write Data

        // Write Elf Header
        res = m_ehdrBuilder.Write(writer);
        if (!res.IsOk()) return res;

        // Write Program Headers
        if (m_phdrBuilder.GetCount() > 0) {
            res = m_phdrBuilder.Write(writer);
            if (!res.IsOk()) return res;
        }

        // Write Sections
        // Current position in file should match layout logic
        // We rely on LayoutManager's logic, but we need to actually write padding

        // Reset layout tracker to track file writing position?
        // Or just Tell() the writer.
        // Writer should correspond to layout.

        for (size_t i = 1; i < m_sections.size(); ++i) {
            auto& section = m_sections[i];

            // Padding
            uint64_t currentPos = static_cast<uint64_t>(writer.Tell());
            uint64_t align = section->GetHeader().sh_addralign;
            uint64_t padding = Layout::LayoutManager::CalculatePadding(currentPos, align);

            res = writer.WritePadding(padding);
            if (!res.IsOk()) return res;

            // Verify offset matches calculated offset
            if (static_cast<uint64_t>(writer.Tell()) != section->GetHeader().sh_offset) {
                // This shouldn't happen if logic is consistent
                return Common::Result::Fail(Common::StatusCode::WriteError, "Section offset mismatch during write.");
            }

            // Write Content
            res = section->Write(writer);
            if (!res.IsOk()) return res;
        }

        // Write Section Headers
        // Padding
        uint64_t currentPos = static_cast<uint64_t>(writer.Tell());
        uint64_t shdrPadding = Layout::LayoutManager::CalculatePadding(currentPos, 8);
        res = writer.WritePadding(shdrPadding);
        if (!res.IsOk()) return res;

        // Build Shdrs
        // Clear existing (if any) and rebuild from m_sections
        // Note: m_shdrBuilder might have been used manually?
        // No, we should populate it from m_sections.
        // But what if user added segments? m_phdrBuilder is separate.

        // We need to clear m_shdrBuilder and populate it.
        // But m_shdrBuilder doesn't have Clear().
        // Actually, we can just *add* to it?
        // If the user manually added headers to m_shdrBuilder, we might duplicate.
        // The design implies m_shdrBuilder is used *by* Build(), not pre-populated.
        // But GetSectionHeaderBuilder() is public.
        // Let's assume we construct a *new* list for writing, or clear it.
        // Since ShdrBuilder doesn't have Clear, let's just make a local one?
        // But PhdrBuilder and EhdrBuilder are members.

        // Let's assume m_shdrBuilder is intended to be populated by Build() only.
        // I will assume it's empty or I'll just use a local loop to write.

        Components::ShdrBuilder finalShdrs;

        // Add NULL section header
        Model::Elf64_Shdr nullShdr{};
        finalShdrs.AddSection(nullShdr);

        for (size_t i = 1; i < m_sections.size(); ++i) {
            finalShdrs.AddSection(m_sections[i]->GetHeader());
        }

        res = finalShdrs.Write(writer);
        if (!res.IsOk()) return res;

        return Common::Result::Ok();
    }

}
