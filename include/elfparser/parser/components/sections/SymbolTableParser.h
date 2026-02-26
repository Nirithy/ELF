#pragma once

#include <vector>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class SymbolTableParser {
    public:
        // Reads symbol table entries from a section.
        // Converts 32-bit entries to 64-bit format if necessary.
        Common::Result Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Sym>& symbols);
    };

}
