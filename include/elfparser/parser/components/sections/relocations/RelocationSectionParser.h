#pragma once

#include <vector>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class RelocationSectionParser {
    public:
        // Reads relocation entries.
        // Determines if it is REL or RELA based on section type.
        // Converts 32-bit to 64-bit RELA format (normalizing REL to RELA by setting addend to 0).
        Common::Result Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Rela>& relocations);
    };

}
