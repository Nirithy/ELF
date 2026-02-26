#pragma once

#include "elfparser/builder/components/segments/SegmentBuilder.h"

namespace ElfParser::Builder::Components {

    class LoadSegmentBuilder : public SegmentBuilder {
    public:
        LoadSegmentBuilder();

        // Load segments enforce alignment strictly.
        // This override might add padding logic if LayoutManager delegates it.
        void Finalize(Layout::LayoutManager& layout) override;
    };

}
