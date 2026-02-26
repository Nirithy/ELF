#pragma once

#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"
#include <vector>

namespace ElfParser::Parser::Components {

    class GnuHashSectionParser {
    public:
        GnuHashSectionParser() = default;
        ~GnuHashSectionParser() = default;

        // Parses GNU Hash Section
        Common::Result Parse(IO::BinaryReader& reader,
                             const Model::Elf64_Ehdr& ehdr,
                             const Model::Elf64_Shdr& shdr,
                             Model::Elf_GnuHash& header,
                             std::vector<uint64_t>& bloomFilter,
                             std::vector<uint32_t>& buckets,
                             std::vector<uint32_t>& chain);
    };

}
