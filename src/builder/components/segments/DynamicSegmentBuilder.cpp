#include "elfparser/builder/components/segments/DynamicSegmentBuilder.h"

namespace ElfParser::Builder::Components {

    DynamicSegmentBuilder::DynamicSegmentBuilder()
        : SegmentBuilder(Model::ElfSegmentType::Dynamic) {
        SetAlign(0x8); // Often 8-byte aligned
        SetFlags(0x6); // R | W
    }

    void DynamicSegmentBuilder::Finalize(Layout::LayoutManager& layout) {
        SegmentBuilder::Finalize(layout);
    }

}
