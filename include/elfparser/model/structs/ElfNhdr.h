#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    struct Elf32_Nhdr {
        uint32_t n_namesz;
        uint32_t n_descsz;
        uint32_t n_type;
    };

    struct Elf64_Nhdr {
        uint32_t n_namesz;
        uint32_t n_descsz;
        uint32_t n_type;
    };

    #pragma pack(pop)
}
