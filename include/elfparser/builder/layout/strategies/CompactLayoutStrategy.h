#pragma once

#include "elfparser/builder/layout/strategies/ILayoutStrategy.h"

namespace ElfParser::Builder::Layout::Strategies {

    /**
     * @brief A layout strategy that attempts to minimize file size by reordering orphan sections
     * to reduce alignment padding.
     */
    class CompactLayoutStrategy : public ILayoutStrategy {
    public:
        void Apply(
            LayoutManager& manager,
            std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
            std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
        ) override;
    };

}
