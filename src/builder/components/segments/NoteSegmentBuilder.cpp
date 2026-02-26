#include "elfparser/builder/components/segments/NoteSegmentBuilder.h"

namespace ElfParser::Builder::Components {

    NoteSegmentBuilder::NoteSegmentBuilder()
        : SegmentBuilder(Model::ElfSegmentType::Note) {
        SetAlign(0x4); // Note alignment
        SetFlags(0x4); // R
    }

    void NoteSegmentBuilder::Finalize(Layout::LayoutManager& layout) {
        SegmentBuilder::Finalize(layout);
    }

}
