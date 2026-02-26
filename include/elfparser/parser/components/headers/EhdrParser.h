#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class EhdrParser {
    public:
        // Reads and validates the ELF Header.
        // Sets the endianness of the reader based on the header.
        Common::Result Parse(IO::BinaryReader& reader, Model::Elf64_Ehdr& header);
    };

}
