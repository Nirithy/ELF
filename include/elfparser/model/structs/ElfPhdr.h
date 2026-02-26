#pragma once

#include <cstdint>
#include "elfparser/model/enums/ElfSegmentType.h"

namespace ElfParser::Model {

    #pragma pack(push, 1)

    // Program Header (32-bit)
    struct Elf32_Phdr {
        uint32_t p_type;
        uint32_t p_offset;
        uint32_t p_vaddr;
        uint32_t p_paddr;
        uint32_t p_filesz;
        uint32_t p_memsz;
        uint32_t p_flags;
        uint32_t p_align;
    };

    // Program Header (64-bit)
    struct Elf64_Phdr {
        uint32_t p_type;
        uint32_t p_flags;
        uint64_t p_offset;
        uint64_t p_vaddr;
        uint64_t p_paddr;
        uint64_t p_filesz;
        uint64_t p_memsz;
        uint64_t p_align;
    };

    #pragma pack(pop)
}
