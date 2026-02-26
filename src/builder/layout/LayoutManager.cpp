#include "elfparser/builder/layout/LayoutManager.h"
#include <algorithm>

namespace ElfParser::Builder::Layout {

    LayoutManager::LayoutManager(uint64_t startOffset)
        : m_currentOffset(startOffset) {}

    uint64_t LayoutManager::Align(uint64_t alignment) {
        if (alignment <= 1) return 0;

        uint64_t padding = CalculatePadding(m_currentOffset, alignment);
        m_currentOffset += padding;
        return padding;
    }

    uint64_t LayoutManager::GetCurrentOffset() const {
        return m_currentOffset;
    }

    void LayoutManager::Advance(uint64_t size) {
        m_currentOffset += size;
    }

    uint64_t LayoutManager::CalculatePadding(uint64_t offset, uint64_t alignment) {
        if (alignment <= 1) return 0;

        uint64_t remainder = offset % alignment;
        if (remainder == 0) return 0;

        return alignment - remainder;
    }

}
