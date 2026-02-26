#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <vector>

namespace ElfParser::Parser::Components {

    class HashSectionParser {
    public:
        HashSectionParser() = default;
        ~HashSectionParser() = default;

        // Parses SysV Hash Section
        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Shdr& shdr,
                             Model::Elf_Hash& header,
                             std::vector<uint32_t>& buckets,
                             std::vector<uint32_t>& chains);
    };

}
