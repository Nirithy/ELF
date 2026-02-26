#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "elfparser/model/ElfStructures.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/layout/LayoutManager.h"

namespace ElfParser::Builder::Components {

    class SegmentBuilder {
    public:
        explicit SegmentBuilder(Model::ElfSegmentType type);
        virtual ~SegmentBuilder() = default;

        // Configuration
        void SetFlags(uint32_t flags);
        void SetVAddr(uint64_t vaddr);
        void SetPAddr(uint64_t paddr);
        void SetAlign(uint64_t align);
        void SetFileSize(uint64_t fileSize);
        void SetMemSize(uint64_t memSize);

        // Section Management
        void AddSection(SectionBuilder* section);
        const std::vector<SectionBuilder*>& GetSections() const;

        // Layout Calculation
        // Computes the size and offset based on sections if applicable.
        // Returns the final segment header.
        virtual void Finalize(Layout::LayoutManager& layout);

        // Accessors
        const Model::Elf64_Phdr& GetHeader() const;
        Model::ElfSegmentType GetType() const;

    protected:
        Model::Elf64_Phdr m_header{};
        std::vector<SectionBuilder*> m_sections;
    };

}
