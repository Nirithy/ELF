#pragma once

#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components {

    class DynamicSegmentBuilder : public SegmentBuilder {
    public:
        DynamicSegmentBuilder();

        // Dynamic segment often points specifically to .dynamic section
        void Finalize(Layout::LayoutManager& layout) override;
    };

}
