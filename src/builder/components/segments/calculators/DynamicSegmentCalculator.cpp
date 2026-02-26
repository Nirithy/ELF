#include "elfparser/builder/components/segments/calculators/DynamicSegmentCalculator.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components::Segments::Calculators {

    void DynamicSegmentCalculator::Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) {
        // Base calculation
        DefaultSegmentCalculator::Calculate(builder, layout);

        auto& header = builder.GetHeaderRef();

        // PT_DYNAMIC specific logic
        // p_filesz == p_memsz usually
        // p_flags = R | W (0x6) typically

        if (header.p_flags == 0) {
            header.p_flags = 0x6; // Read | Write
        }

        if (header.p_align == 0) {
            header.p_align = 0x8;
        }

        if (header.p_memsz < header.p_filesz) {
            header.p_memsz = header.p_filesz;
        }
    }

}
