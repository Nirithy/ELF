#pragma once

#include <cstdint>
#include <vector>
#include "elfparser/common/Types.h"

namespace ElfParser::Builder::Layout {

    class LayoutManager {
    public:
        explicit LayoutManager(uint64_t startOffset = 0);

        // Aligns the current offset to the given alignment
        // Returns the number of padding bytes added.
        uint64_t Align(uint64_t alignment);

        // Returns the current offset
        uint64_t GetCurrentOffset() const;

        // Advances the offset by size
        void Advance(uint64_t size);

        // Static helper to calculate padding needed
        static uint64_t CalculatePadding(uint64_t offset, uint64_t alignment);

    private:
        uint64_t m_currentOffset;
    };

}
