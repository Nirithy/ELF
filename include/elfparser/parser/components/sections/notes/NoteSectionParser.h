#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <vector>
#include <string>

namespace ElfParser::Parser::Components {

    struct ElfNoteEntry {
        uint32_t type;
        std::string name;
        std::vector<unsigned char> descriptor;
    };

    class NoteSectionParser {
    public:
        NoteSectionParser() = default;
        ~NoteSectionParser() = default;

        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Ehdr& ehdr,
                             const Model::Elf64_Shdr& shdr,
                             std::vector<ElfNoteEntry>& notes);
    };

}
