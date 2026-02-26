#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    class RelocationSectionBuilder : public SectionBuilder {
    public:
        explicit RelocationSectionBuilder(const std::string& name = ".rela.text");

        // Adds a fully constructed relocation entry.
        void AddRelocation(const Model::Elf64_Rela& rela);

        // Helper to construct and add a relocation entry.
        void AddRelocation(uint64_t offset, uint32_t type, uint32_t symIdx, int64_t addend);

        // Helper to construct r_info field
        static uint64_t MakeInfo(uint32_t symIdx, uint32_t type) {
            return (static_cast<uint64_t>(symIdx) << 32) + (type);
        }

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        std::vector<Model::Elf64_Rela> m_relocations;
    };

}
