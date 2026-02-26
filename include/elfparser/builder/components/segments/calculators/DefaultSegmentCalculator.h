#pragma once

#include "elfparser/builder/components/segments/calculators/ISegmentCalculator.h"

namespace ElfParser::Builder::Components::Segments::Calculators {

    class DefaultSegmentCalculator : public ISegmentCalculator {
    public:
        void Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) override;
    };

}
