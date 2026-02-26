#pragma once

#include <vector>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class DynamicSectionParser {
    public:
        // Reads dynamic section entries.
        // Converts 32-bit entries to 64-bit format.
        Common::Result Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Dyn>& dynamics);
    };

}
