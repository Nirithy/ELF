#include "elfparser/builder/components/segments/calculators/DefaultSegmentCalculator.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include <algorithm>
#include <limits>

namespace ElfParser::Builder::Components::Segments::Calculators {

    void DefaultSegmentCalculator::Calculate(SegmentBuilder& builder, Layout::LayoutManager& layout) {
        // Retrieve current header and sections
        const auto& sections = builder.GetSections();
        auto& header = builder.GetHeaderRef();

        if (sections.empty()) {
            return;
        }

        uint64_t minOffset = std::numeric_limits<uint64_t>::max();
        uint64_t maxEnd = 0;
        uint64_t minVAddr = std::numeric_limits<uint64_t>::max();
        uint64_t maxVEnd = 0;

        bool hasFileSections = false;
        bool hasAllocSections = false;

        for (const auto* section : sections) {
            const auto& secHdr = section->GetHeader();

            // Only consider sections that occupy space in file for file size
            if (secHdr.sh_type != static_cast<uint32_t>(Model::ElfSectionType::Nobits)) {
                minOffset = std::min(minOffset, secHdr.sh_offset);
                maxEnd = std::max(maxEnd, secHdr.sh_offset + secHdr.sh_size);
                hasFileSections = true;
            }

            // Considerations for virtual address
            if (secHdr.sh_flags & 0x2) { // SHF_ALLOC
                minVAddr = std::min(minVAddr, secHdr.sh_addr);
                maxVEnd = std::max(maxVEnd, secHdr.sh_addr + secHdr.sh_size);
                hasAllocSections = true;
            }
        }

        if (hasFileSections && minOffset != std::numeric_limits<uint64_t>::max()) {
            header.p_offset = minOffset;
            header.p_filesz = maxEnd - minOffset;
        } else {
            // NOBITS sections or empty?
            // If NOBITS only, p_offset usually points to start of NOBITS, but filesz is 0.
            if (!hasFileSections && hasAllocSections) {
                 // Try to find the offset where it would be? Usually just keep 0 or inherit from previous?
                 // For now, leave as is or set to 0.
                 header.p_filesz = 0;
            }
        }

        if (hasAllocSections && minVAddr != std::numeric_limits<uint64_t>::max()) {
            header.p_vaddr = minVAddr;
            header.p_paddr = minVAddr; // Usually same as vaddr
            header.p_memsz = maxVEnd - minVAddr;
        } else {
            // No alloc sections
            header.p_memsz = 0;
        }
    }

}
