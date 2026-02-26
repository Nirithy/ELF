#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <vector>

namespace ElfParser::Parser::Components {

    struct VersionRequirementEntry {
        Model::Elf_Verneed need;
        std::vector<Model::Elf_Vernaux> auxiliaries;
    };

    class VersionRequirementParser {
    public:
        VersionRequirementParser() = default;
        ~VersionRequirementParser() = default;

        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Shdr& shdr,
                             std::vector<VersionRequirementEntry>& requirements);
    };

}
