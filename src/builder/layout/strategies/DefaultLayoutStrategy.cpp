#include "elfparser/builder/layout/strategies/DefaultLayoutStrategy.h"
#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include <set>
#include <algorithm>

namespace ElfParser::Builder::Layout::Strategies {

    void DefaultLayoutStrategy::Apply(
        LayoutManager& manager,
        std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
        std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
    ) {
        std::set<Components::SectionBuilder*> placedSections;

        // 1. Place segments and their sections
        for (auto& segment : segments) {
            if (!segment) continue;

            // Align segment
            const auto& hdr = segment->GetHeader();
            if (hdr.p_align > 1) {
                manager.Align(hdr.p_align);
            }

            // Iterate sections in this segment
            for (auto* section : segment->GetSections()) {
                if (placedSections.find(section) != placedSections.end()) {
                    continue; // Already placed
                }

                // Align section
                uint64_t align = section->GetHeader().sh_addralign;
                if (align > 1) {
                    manager.Align(align);
                }

                // Set section offset
                uint64_t offset = manager.GetCurrentOffset();
                uint64_t size = section->GetSize();

                // Update section header
                section->UpdateHeader(offset, size);

                // Advance
                manager.Advance(size);

                placedSections.insert(section);
            }

            // Finalize segment
            segment->Finalize(manager);
        }

        // 2. Place remaining sections (orphans)
        for (auto& section : sections) {
            if (!section) continue;

            if (placedSections.find(section.get()) == placedSections.end()) {
                 // Align section
                uint64_t align = section->GetHeader().sh_addralign;
                if (align > 1) {
                    manager.Align(align);
                }

                // Set section offset
                uint64_t offset = manager.GetCurrentOffset();
                uint64_t size = section->GetSize();

                // Update section header
                section->UpdateHeader(offset, size);

                // Advance
                manager.Advance(size);

                placedSections.insert(section.get());
            }
        }
    }

}
