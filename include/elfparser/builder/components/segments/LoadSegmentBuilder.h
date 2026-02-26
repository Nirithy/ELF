#pragma once

#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components {

    class LoadSegmentBuilder : public SegmentBuilder {
    public:
        LoadSegmentBuilder();
        // Uses LoadSegmentCalculator initialized in constructor.
    };

}
