#include "elfparser/builder/components/segments/DynamicSegmentBuilder.h"
#include "elfparser/builder/components/segments/calculators/DynamicSegmentCalculator.h"

namespace ElfParser::Builder::Components {

    DynamicSegmentBuilder::DynamicSegmentBuilder()
        : SegmentBuilder(Model::ElfSegmentType::Dynamic) {
        SetAlign(0x8);
        SetFlags(0x6); // R | W

        SetCalculator(std::make_unique<Segments::Calculators::DynamicSegmentCalculator>());
    }

}
