#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    struct Elf_Verdef {
        uint16_t vd_version;
        uint16_t vd_flags;
        uint16_t vd_ndx;
        uint16_t vd_cnt;
        uint32_t vd_hash;
        uint32_t vd_aux;
        uint32_t vd_next;
    };

    struct Elf_Verdaux {
        uint32_t vda_name;
        uint32_t vda_next;
    };

    #pragma pack(pop)
}
