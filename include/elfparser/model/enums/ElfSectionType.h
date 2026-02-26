#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfSectionType : uint32_t {
        Null = 0,
        Progbits = 1,
        Symtab = 2,
        Strtab = 3,
        Rela = 4,
        Hash = 5,
        Dynamic = 6,
        Note = 7,
        Nobits = 8,
        Rel = 9,
        Shlib = 10,
        Dynsym = 11,
        InitArray = 14,
        FiniArray = 15,
        PreinitArray = 16,
        Group = 17,
        SymTabShndx = 18,
        GnuAttributes = 0x6ffffff5,
        GnuHash = 0x6ffffff6,
        GnuLibList = 0x6ffffff7,
        Checksum = 0x6ffffff8,
        SunWMove = 0x6ffffffa,
        SunWComdat = 0x6ffffffb,
        SunWSymInfo = 0x6ffffffc,
        GnuVerDef = 0x6ffffffd,
        GnuVerNeed = 0x6ffffffe,
        GnuVerSym = 0x6fffffff
    };
}
