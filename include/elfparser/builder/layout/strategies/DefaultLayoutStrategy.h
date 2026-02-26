#pragma once

#include "elfparser/builder/layout/strategies/ILayoutStrategy.h"
#include <set>

namespace ElfParser::Builder::Layout::Strategies {

    class DefaultLayoutStrategy : public ILayoutStrategy {
    public:
        void Apply(
            LayoutManager& manager,
            std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
            std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
        ) override;
    };

}
