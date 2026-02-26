#pragma once

#include "elfparser/builder/components/segments/calculators/DefaultSegmentCalculator.h"

namespace ElfParser::Builder::Components::Segments::Calculators {

    class LoadSegmentCalculator : public DefaultSegmentCalculator {
    public:
        void Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) override;
    };

}
