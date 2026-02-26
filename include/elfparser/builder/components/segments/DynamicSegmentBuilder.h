#pragma once

#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components {

    class DynamicSegmentBuilder : public SegmentBuilder {
    public:
        DynamicSegmentBuilder();
        // Uses DynamicSegmentCalculator.
    };

}
