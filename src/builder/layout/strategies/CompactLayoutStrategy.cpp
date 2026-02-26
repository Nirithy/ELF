#include "elfparser/builder/layout/strategies/CompactLayoutStrategy.h"
#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include <set>
#include <algorithm>
#include <vector>

namespace ElfParser::Builder::Layout::Strategies {

    void CompactLayoutStrategy::Apply(
        LayoutManager& manager,
        std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
        std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
    ) {
        // For segments, we must respect their order generally, as they might be load segments.
        // But for orphans, we can reorder.

        std::set<Components::SectionBuilder*> placedSections;

        // 1. Process Segments (strict order)
        for (auto& segment : segments) {
            if (!segment) continue;

            // Align segment
            if (segment->GetHeader().p_align > 1) {
                manager.Align(segment->GetHeader().p_align);
            }

            for (auto* section : segment->GetSections()) {
                if (placedSections.find(section) != placedSections.end()) continue;

                if (section->GetHeader().sh_addralign > 1) {
                    manager.Align(section->GetHeader().sh_addralign);
                }

                section->UpdateHeader(manager.GetCurrentOffset(), section->GetSize());
                manager.Advance(section->GetSize());
                placedSections.insert(section);
            }
            segment->Finalize(manager);
        }

        // 2. Process Orphans - Sort by Alignment (descending) to minimize padding
        std::vector<Components::SectionBuilder*> orphans;
        for (auto& section : sections) {
            if (section && placedSections.find(section.get()) == placedSections.end()) {
                orphans.push_back(section.get());
            }
        }

        std::sort(orphans.begin(), orphans.end(), [](Components::SectionBuilder* a, Components::SectionBuilder* b) {
            return a->GetHeader().sh_addralign > b->GetHeader().sh_addralign;
        });

        for (auto* section : orphans) {
            if (section->GetHeader().sh_addralign > 1) {
                manager.Align(section->GetHeader().sh_addralign);
            }
            section->UpdateHeader(manager.GetCurrentOffset(), section->GetSize());
            manager.Advance(section->GetSize());
        }
    }

}
