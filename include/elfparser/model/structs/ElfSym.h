#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    // Symbol Table Entry (32-bit)
    struct Elf32_Sym {
        uint32_t st_name;
        uint32_t st_value;
        uint32_t st_size;
        unsigned char st_info;
        unsigned char st_other;
        uint16_t st_shndx;
    };

    // Symbol Table Entry (64-bit)
    struct Elf64_Sym {
        uint32_t st_name;
        unsigned char st_info;
        unsigned char st_other;
        uint16_t st_shndx;
        uint64_t st_value;
        uint64_t st_size;
    };

    #pragma pack(pop)
}
