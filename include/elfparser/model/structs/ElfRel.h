#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    // Relocation Entry (32-bit)
    struct Elf32_Rel {
        uint32_t r_offset;
        uint32_t r_info;
    };

    // Relocation Entry with Addend (32-bit)
    struct Elf32_Rela {
        uint32_t r_offset;
        uint32_t r_info;
        int32_t r_addend;
    };

    // Relocation Entry (64-bit)
    struct Elf64_Rel {
        uint64_t r_offset;
        uint64_t r_info;
    };

    // Relocation Entry with Addend (64-bit)
    struct Elf64_Rela {
        uint64_t r_offset;
        uint64_t r_info;
        int64_t r_addend;
    };

    #pragma pack(pop)
}
