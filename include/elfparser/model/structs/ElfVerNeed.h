#pragma once

#include <cstdint>

namespace ElfParser::Model {

    #pragma pack(push, 1)

    struct Elf_Verneed {
        uint16_t vn_version;
        uint16_t vn_cnt;
        uint32_t vn_file;
        uint32_t vn_aux;
        uint32_t vn_next;
    };

    struct Elf_Vernaux {
        uint32_t vna_hash;
        uint16_t vna_flags;
        uint16_t vna_other;
        uint32_t vna_name;
        uint32_t vna_next;
    };

    #pragma pack(pop)
}
