#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include <algorithm>
#include <limits>

namespace ElfParser::Builder::Components {

    SegmentBuilder::SegmentBuilder(Model::ElfSegmentType type) {
        m_header.p_type = static_cast<uint32_t>(type);
        m_header.p_flags = 0;
        m_header.p_offset = 0;
        m_header.p_vaddr = 0;
        m_header.p_paddr = 0;
        m_header.p_filesz = 0;
        m_header.p_memsz = 0;
        m_header.p_align = 0x1000; // Default page alignment
    }

    void SegmentBuilder::SetFlags(uint32_t flags) {
        m_header.p_flags = flags;
    }

    void SegmentBuilder::SetVAddr(uint64_t vaddr) {
        m_header.p_vaddr = vaddr;
    }

    void SegmentBuilder::SetPAddr(uint64_t paddr) {
        m_header.p_paddr = paddr;
    }

    void SegmentBuilder::SetAlign(uint64_t align) {
        m_header.p_align = align;
    }

    void SegmentBuilder::SetFileSize(uint64_t fileSize) {
        m_header.p_filesz = fileSize;
    }

    void SegmentBuilder::SetMemSize(uint64_t memSize) {
        m_header.p_memsz = memSize;
    }

    void SegmentBuilder::AddSection(SectionBuilder* section) {
        if (section) {
            m_sections.push_back(section);
        }
    }

    const std::vector<SectionBuilder*>& SegmentBuilder::GetSections() const {
        return m_sections;
    }

    void SegmentBuilder::Finalize(Layout::LayoutManager& layout) {
        // If we have sections, derive segment bounds from them
        if (!m_sections.empty()) {
            uint64_t minOffset = std::numeric_limits<uint64_t>::max();
            uint64_t maxEnd = 0;
            uint64_t minVAddr = std::numeric_limits<uint64_t>::max();
            uint64_t maxVEnd = 0;

            for (const auto* section : m_sections) {
                const auto& hdr = section->GetHeader();

                // Only consider sections that occupy space in file for file size
                if (hdr.sh_type != static_cast<uint32_t>(Model::ElfSectionType::Nobits)) {
                    minOffset = std::min(minOffset, hdr.sh_offset);
                    maxEnd = std::max(maxEnd, hdr.sh_offset + hdr.sh_size);
                }

                // Considerations for virtual address
                if (hdr.sh_flags & 0x2) { // SHF_ALLOC
                    minVAddr = std::min(minVAddr, hdr.sh_addr);
                    maxVEnd = std::max(maxVEnd, hdr.sh_addr + hdr.sh_size);
                }
            }

            if (minOffset != std::numeric_limits<uint64_t>::max()) {
                m_header.p_offset = minOffset;
                m_header.p_filesz = maxEnd - minOffset;
            }

            if (minVAddr != std::numeric_limits<uint64_t>::max()) {
                m_header.p_vaddr = minVAddr;
                m_header.p_paddr = minVAddr; // Usually same as vaddr
                m_header.p_memsz = maxVEnd - minVAddr;
            } else {
                // If only file-backed sections (no alloc), memsz is usually filesz or 0 depending on segment type
                // But generally segments without ALLOC sections aren't LOAD segments.
            }

            // If it's a LOAD segment, ensure memsz >= filesz
            if (m_header.p_type == static_cast<uint32_t>(Model::ElfSegmentType::Load)) {
                if (m_header.p_memsz < m_header.p_filesz) {
                     m_header.p_memsz = m_header.p_filesz;
                }
            }
        }
    }

    const Model::Elf64_Phdr& SegmentBuilder::GetHeader() const {
        return m_header;
    }

    Model::ElfSegmentType SegmentBuilder::GetType() const {
        return static_cast<Model::ElfSegmentType>(m_header.p_type);
    }

}
