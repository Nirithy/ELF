#include "elfparser/builder/components/segments/LoadSegmentBuilder.h"
#include "elfparser/builder/components/segments/calculators/LoadSegmentCalculator.h"

namespace ElfParser::Builder::Components {

    LoadSegmentBuilder::LoadSegmentBuilder()
        : SegmentBuilder(Model::ElfSegmentType::Load) {
        SetAlign(0x1000); // Standard page size
        SetFlags(0x5); // R | X (Default to code, can be changed)

        // Set the specific calculator
        SetCalculator(std::make_unique<Segments::Calculators::LoadSegmentCalculator>());
    }

}
