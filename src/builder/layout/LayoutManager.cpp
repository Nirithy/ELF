#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/builder/layout/strategies/DefaultLayoutStrategy.h"
#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"

namespace ElfParser::Builder::Layout {

    LayoutManager::LayoutManager(uint64_t startOffset)
        : m_currentOffset(startOffset) {
        // Default strategy
        m_strategy = std::make_unique<Strategies::DefaultLayoutStrategy>();
    }

    LayoutManager::~LayoutManager() = default;

    uint64_t LayoutManager::Align(uint64_t alignment) {
        if (alignment == 0 || alignment == 1) {
            return 0;
        }
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

    void LayoutManager::SetStrategy(std::unique_ptr<Strategies::ILayoutStrategy> strategy) {
        if (strategy) {
            m_strategy = std::move(strategy);
        }
    }

    uint64_t LayoutManager::CalculatePadding(uint64_t offset, uint64_t alignment) {
        if (alignment == 0 || alignment == 1) {
            return 0;
        }
        uint64_t remainder = offset % alignment;
        if (remainder == 0) {
            return 0;
        }
        return alignment - remainder;
    }

    void LayoutManager::ComputeLayout(
        std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
        std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
    ) {
        if (m_strategy) {
            m_strategy->Apply(*this, segments, sections);
        }
    }

}
