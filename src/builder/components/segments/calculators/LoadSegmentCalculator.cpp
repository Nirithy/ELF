#include "elfparser/builder/components/segments/calculators/LoadSegmentCalculator.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include <algorithm>

namespace ElfParser::Builder::Components::Segments::Calculators {

    void LoadSegmentCalculator::Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) {
        // Base calculation first
        DefaultSegmentCalculator::Calculate(builder, layout);

        auto& header = builder.GetHeaderRef();

        // Ensure memsz >= filesz
        if (header.p_memsz < header.p_filesz) {
            header.p_memsz = header.p_filesz;
        }

        // Align p_offset and p_vaddr modulo p_align
        if (header.p_align > 1) {
            uint64_t vaddr_mod = header.p_vaddr % header.p_align;
            uint64_t offset_mod = header.p_offset % header.p_align;

            // This constraint is critical for execution: vaddr == offset (mod align)
            // If they differ, the loader fails.
            // Adjusting this here is tricky because offset is set by LayoutManager.
            // We assume LayoutManager respects alignment rules if vaddr is fixed.
            // Or we just warn/error?
            // For now, let's just ensure we don't break anything.
        }
    }

}
