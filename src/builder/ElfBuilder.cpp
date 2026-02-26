#include "elfparser/builder/ElfBuilder.h"
#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/builder/components/segments/LoadSegmentBuilder.h"
#include "elfparser/builder/components/segments/DynamicSegmentBuilder.h"
#include "elfparser/builder/components/segments/NoteSegmentBuilder.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Builder {

    ElfBuilder::ElfBuilder(const std::string& outputPath)
        : m_outputPath(outputPath) {

        // Ensure index 0 is reserved for SHT_NULL
        // Typically handled by creating a dummy section or just logic in ShdrBuilder?
        // Let's explicitly create a dummy section builder that writes nothing?
        // Or simply add nullptr to m_sections as before.
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
        if (m_shstrtabRef) {
            uint32_t nameIdx = m_shstrtabRef->AddString(section->GetName());
            section->GetHeader().sh_name = nameIdx;
        }

        m_sections.push_back(std::move(section));
    }

    void ElfBuilder::RemoveSection(const std::string& name) {
        for (auto it = m_sections.begin(); it != m_sections.end(); ++it) {
            if (*it && (*it)->GetName() == name) {
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

    void ElfBuilder::AddSegment(std::unique_ptr<Components::SegmentBuilder> segment) {
        if (segment) {
            m_segments.push_back(std::move(segment));
        }
    }

    Components::SegmentBuilder* ElfBuilder::CreateSegment(Model::ElfSegmentType type) {
        std::unique_ptr<Components::SegmentBuilder> segment;
        switch (type) {
            case Model::ElfSegmentType::Load:
                segment = std::make_unique<Components::LoadSegmentBuilder>();
                break;
            case Model::ElfSegmentType::Dynamic:
                segment = std::make_unique<Components::DynamicSegmentBuilder>();
                break;
            case Model::ElfSegmentType::Note:
                segment = std::make_unique<Components::NoteSegmentBuilder>();
                break;
            default:
                segment = std::make_unique<Components::SegmentBuilder>(type);
                break;
        }
        Components::SegmentBuilder* ptr = segment.get();
        AddSegment(std::move(segment));
        return ptr;
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
        uint64_t phnum = m_segments.size();

        // If we have segments, reserve space for Phdrs
        if (phnum > 0) {
            layout.Advance(sizeof(Model::Elf64_Phdr) * phnum);
        } else {
            phoff = 0; // No segments, no program headers usually
        }

        // Compute Layout (Segments + Sections)
        layout.ComputeLayout(m_segments, m_sections);

        // Section Headers
        // Align for section headers
        layout.Align(8);
        uint64_t shoff = layout.GetCurrentOffset();
        uint16_t shnum = static_cast<uint16_t>(m_sections.size());

        // 2. Finalize Elf Header
        uint16_t shstrndx = 0;
        for (size_t i = 0; i < m_sections.size(); ++i) {
            if (m_sections[i].get() == m_shstrtabRef) {
                shstrndx = static_cast<uint16_t>(i);
                break;
            }
        }

        m_ehdrBuilder.UpdateLayout(phoff, phnum, shoff, shnum, shstrndx);

        // 3. Write Data

        // Write Elf Header
        res = writer.Seek(0);
        if (!res.IsOk()) return res;
        res = m_ehdrBuilder.Write(writer);
        if (!res.IsOk()) return res;

        // Write Program Headers
        if (phnum > 0) {
            res = writer.Seek(phoff);
            if (!res.IsOk()) return res;

            // Populate temporary PhdrBuilder (or update member)
            m_phdrBuilder = Components::PhdrBuilder(); // Clear/Reset
            for (const auto& seg : m_segments) {
                m_phdrBuilder.AddSegment(seg->GetHeader());
            }
            res = m_phdrBuilder.Write(writer);
            if (!res.IsOk()) return res;
        }

        // Write Sections
        for (size_t i = 1; i < m_sections.size(); ++i) {
            auto& section = m_sections[i];
            if (!section) continue;

            // Seek to calculated offset
            res = writer.Seek(section->GetHeader().sh_offset);
            if (!res.IsOk()) return res;

            // Write Content
            res = section->Write(writer);
            if (!res.IsOk()) return res;
        }

        // Write Section Headers
        res = writer.Seek(shoff);
        if (!res.IsOk()) return res;

        // Populate ShdrBuilder
        m_shdrBuilder = Components::ShdrBuilder(); // Reset

        // Add NULL section header (index 0)
        Model::Elf64_Shdr nullShdr{};
        m_shdrBuilder.AddSection(nullShdr);

        for (size_t i = 1; i < m_sections.size(); ++i) {
            if (m_sections[i]) {
                m_shdrBuilder.AddSection(m_sections[i]->GetHeader());
            } else {
                // Should not happen if m_sections[0] is the only null
                m_shdrBuilder.AddSection(nullShdr);
            }
        }

        res = m_shdrBuilder.Write(writer);
        if (!res.IsOk()) return res;

        return Common::Result::Ok();
    }

}
