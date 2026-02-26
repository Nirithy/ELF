#pragma once

#include <vector>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class SegmentParser {
    public:
        // Reads all program headers from the file.
        Common::Result ParseHeaders(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, std::vector<Model::Elf64_Phdr>& segments);
    };

}
