#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "elfparser/common/Types.h"

// Forward declarations
namespace ElfParser::Builder::Components {
    class SegmentBuilder;
    class SectionBuilder;
}

namespace ElfParser::Builder::Layout {

    namespace Strategies {
        class ILayoutStrategy;
    }

    class LayoutManager {
    public:
        explicit LayoutManager(uint64_t startOffset = 0);
        ~LayoutManager(); // Required for unique_ptr to forward declared type

        // Aligns the current offset to the given alignment
        // Returns the number of padding bytes added.
        uint64_t Align(uint64_t alignment);

        // Returns the current offset
        uint64_t GetCurrentOffset() const;

        // Advances the offset by size
        void Advance(uint64_t size);

        // Set a custom layout strategy
        void SetStrategy(std::unique_ptr<Strategies::ILayoutStrategy> strategy);

        // Computes the layout for segments and sections using the current strategy
        void ComputeLayout(
            std::vector<std::unique_ptr<Components::SegmentBuilder>>& segments,
            std::vector<std::unique_ptr<Components::SectionBuilder>>& sections
        );

        // Static helper to calculate padding needed
        static uint64_t CalculatePadding(uint64_t offset, uint64_t alignment);

    private:
        uint64_t m_currentOffset;
        std::unique_ptr<Strategies::ILayoutStrategy> m_strategy;
    };

}
