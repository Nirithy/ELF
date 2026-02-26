#pragma once

#include <cstdint>
#include "elfparser/model/enums/ElfClass.h"
#include "elfparser/model/enums/ElfData.h"
#include "elfparser/model/enums/ElfOsAbi.h"
#include "elfparser/model/enums/ElfType.h"
#include "elfparser/model/enums/ElfMachine.h"
#include "elfparser/model/enums/ElfVersion.h"

namespace ElfParser::Model {

    // ELF Magic
    constexpr unsigned char ELFMAG[] = { 0x7f, 'E', 'L', 'F' };
    constexpr int SELFMAG = 4;

    // e_ident indices
    constexpr int EI_MAG0 = 0;
    constexpr int EI_MAG1 = 1;
    constexpr int EI_MAG2 = 2;
    constexpr int EI_MAG3 = 3;
    constexpr int EI_CLASS = 4;
    constexpr int EI_DATA = 5;
    constexpr int EI_VERSION = 6;
    constexpr int EI_OSABI = 7;
    constexpr int EI_ABIVERSION = 8;
    constexpr int EI_PAD = 9;
    constexpr int EI_NIDENT = 16;

    #pragma pack(push, 1)

    // ELF Header (32-bit)
    struct Elf32_Ehdr {
        unsigned char e_ident[16];
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint32_t e_entry;
        uint32_t e_phoff;
        uint32_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
    };

    // ELF Header (64-bit)
    struct Elf64_Ehdr {
        unsigned char e_ident[16];
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint64_t e_entry;
        uint64_t e_phoff;
        uint64_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
    };

    #pragma pack(pop)
}
