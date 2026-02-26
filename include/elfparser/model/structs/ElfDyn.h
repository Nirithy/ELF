#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    // Dynamic Section Entry (32-bit)
    struct Elf32_Dyn {
        int32_t d_tag;
        union {
            uint32_t d_val;
            uint32_t d_ptr;
        } d_un;
    };

    // Dynamic Section Entry (64-bit)
    struct Elf64_Dyn {
        int64_t d_tag;
        union {
            uint64_t d_val;
            uint64_t d_ptr;
        } d_un;
    };

    #pragma pack(pop)
}
