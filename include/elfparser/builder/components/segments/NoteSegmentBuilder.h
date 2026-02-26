#pragma once

#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components {

    class NoteSegmentBuilder : public SegmentBuilder {
    public:
        NoteSegmentBuilder();

        void Finalize(Layout::LayoutManager& layout) override;
    };

}
