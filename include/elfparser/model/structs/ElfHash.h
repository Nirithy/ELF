#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    // SysV Hash Header
    struct Elf_Hash {
        uint32_t nbucket;
        uint32_t nchain;
    };

    // GNU Hash Header
    struct Elf_GnuHash {
        uint32_t nbuckets;
        uint32_t symndx;
        uint32_t maskwords;
        uint32_t shift2;
    };

    #pragma pack(pop)
}
