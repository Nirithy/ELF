#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <string>
#include <vector>

namespace ElfParser::Parser::Components {

    class StringTableParser {
    public:
        StringTableParser() = default;
        ~StringTableParser() = default;

        // Reads the entire string table into memory
        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Shdr& shdr,
                             std::vector<char>& tableData);

        // Helper to get string from raw data
        static std::string GetString(const std::vector<char>& tableData, uint32_t offset);
    };

}
