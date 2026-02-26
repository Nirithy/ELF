#pragma once

#include <vector>
#include <memory>
#include "elfparser/common/Types.h"

// Forward declarations
namespace ElfParser::Builder::Components {
    class SegmentBuilder;
    class SectionBuilder;
}

namespace ElfParser::Builder::Layout {
    class LayoutManager;
}

namespace ElfParser::Builder::Layout::Strategies {

    /**
     * @brief Interface for layout strategies that determine how segments and sections
     * are placed in the file.
     */
    class ILayoutStrategy {
    public:
        virtual ~ILayoutStrategy() = default;

        /**
         * @brief Apply the layout strategy.
         *
         * @param manager The layout manager context (for alignment helpers, offset tracking).
         * @param segments List of segments to layout.
         * @param sections List of sections (including orphans) to layout.
         */
        virtual void Apply(
            LayoutManager& manager,
            std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
            std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
        ) = 0;
    };

}
