#pragma once

#include <vector>
#include <string>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser::Components {

    class ShdrParser {
    public:
        Common::Result ParseHeaders(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, std::vector<Model::Elf64_Shdr>& sections);

        Common::Result ParseStringTable(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const std::vector<Model::Elf64_Shdr>& sections, std::vector<char>& strTab);

        static std::string GetSectionName(const std::vector<char>& strTab, uint32_t offset);
    };

}
