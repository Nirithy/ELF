#pragma once

#include <vector>
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryWriter.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Builder::Components {

    class ShdrBuilder {
    public:
        void AddSection(const Model::Elf64_Shdr& shdr);
        const std::vector<Model::Elf64_Shdr>& GetSections() const;
        std::vector<Model::Elf64_Shdr>& GetSections();

        Common::Result Write(IO::BinaryWriter& writer);

        uint16_t GetCount() const;
        uint64_t GetSize() const;

    private:
        std::vector<Model::Elf64_Shdr> m_sections;
    };

}
