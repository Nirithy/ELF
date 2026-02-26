#pragma once

#include "elfparser/common/Types.h"

// Forward declarations
namespace ElfParser::Builder::Layout {
    class LayoutManager;
}

namespace ElfParser::Builder::Components {
    class SegmentBuilder;
}

namespace ElfParser::Builder::Components::Segments::Calculators {

    /**
     * @brief Interface for calculating segment properties (size, flags, etc.).
     */
    class ISegmentCalculator {
    public:
        virtual ~ISegmentCalculator() = default;

        /**
         * @brief Calculates and updates the segment header fields.
         *
         * @param builder The segment builder to update.
         * @param layout The layout manager context.
         */
        virtual void Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) = 0;
    };

}
