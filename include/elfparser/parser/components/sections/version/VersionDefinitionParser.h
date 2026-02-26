#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <vector>

namespace ElfParser::Parser::Components {

    struct VersionDefinitionEntry {
        Model::Elf_Verdef def;
        std::vector<Model::Elf_Verdaux> auxiliaries;
    };

    class VersionDefinitionParser {
    public:
        VersionDefinitionParser() = default;
        ~VersionDefinitionParser() = default;

        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Shdr& shdr,
                             std::vector<VersionDefinitionEntry>& definitions);
    };

}
