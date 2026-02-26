#include "elfparser/builder/components/segments/LoadSegmentBuilder.h"

namespace ElfParser::Builder::Components {

    LoadSegmentBuilder::LoadSegmentBuilder()
        : SegmentBuilder(Model::ElfSegmentType::Load) {
        SetAlign(0x1000); // Standard page size
        SetFlags(0x5); // R | X (Default to code, can be changed)
    }

    void LoadSegmentBuilder::Finalize(Layout::LayoutManager& layout) {
        SegmentBuilder::Finalize(layout);
        // Additional load-specific checks can go here
    }

}
