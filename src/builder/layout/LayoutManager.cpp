#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include <set>
#include <algorithm>

namespace ElfParser::Builder::Layout {

    LayoutManager::LayoutManager(uint64_t startOffset) : m_currentOffset(startOffset) {}

    uint64_t LayoutManager::Align(uint64_t alignment) {
        if (alignment == 0 || alignment == 1) {
            return 0;
        }
        uint64_t padding = CalculatePadding(m_currentOffset, alignment);
        m_currentOffset += padding;
        return padding;
    }

    uint64_t LayoutManager::GetCurrentOffset() const {
        return m_currentOffset;
    }

    void LayoutManager::Advance(uint64_t size) {
        m_currentOffset += size;
    }

    uint64_t LayoutManager::CalculatePadding(uint64_t offset, uint64_t alignment) {
        if (alignment == 0 || alignment == 1) {
            return 0;
        }
        uint64_t remainder = offset % alignment;
        if (remainder == 0) {
            return 0;
        }
        return alignment - remainder;
    }

    void LayoutManager::ComputeLayout(
        std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
        std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
    ) {
        std::set<Components::SectionBuilder*> placedSections;

        // 1. Place segments and their sections
        for (auto& segment : segments) {
            // Align segment start (usually page alignment for LOAD)
            // But strict alignment depends on p_align.
            // For file offset, we usually just align to something reasonable or rely on section alignment.
            // Actually, PT_LOAD p_offset must be congruent to p_vaddr modulo p_align.
            // This is complex. For now, we simply align the current file offset to p_align if set.

            const auto& hdr = segment->GetHeader();
            if (hdr.p_align > 1) {
                Align(hdr.p_align);
            }

            // Note: We don't set segment p_offset here explicitly, segment->Finalize() will derive it
            // from the first section's offset.

            // Iterate sections in this segment
            for (auto* section : segment->GetSections()) {
                if (placedSections.find(section) != placedSections.end()) {
                    // Already placed? (e.g., in multiple segments).
                    // We assume the first segment dictates placement.
                    continue;
                }

                // Align section
                uint64_t align = section->GetHeader().sh_addralign;
                if (align > 1) {
                    Align(align);
                }

                // Set section offset
                uint64_t offset = m_currentOffset;
                uint64_t size = section->GetSize();

                // Update section header
                section->UpdateHeader(offset, size);

                // Advance
                Advance(size);

                placedSections.insert(section);
            }

            // Now finalize the segment (calculate p_offset, p_filesz, etc. based on sections)
            segment->Finalize(*this);
        }

        // 2. Place remaining sections (orphans)
        for (auto& section : sections) {
            if (!section) continue;

            if (placedSections.find(section.get()) == placedSections.end()) {
                 // Align section
                uint64_t align = section->GetHeader().sh_addralign;
                if (align > 1) {
                    Align(align);
                }

                // Set section offset
                uint64_t offset = m_currentOffset;
                uint64_t size = section->GetSize();

                // Update section header
                section->UpdateHeader(offset, size);

                // Advance
                Advance(size);

                placedSections.insert(section.get());
            }
        }
    }

}
