#pragma once

#include <cstdint>

namespace ElfParser::Model {

    enum class ElfDynamicTag : int64_t {
        Null = 0,
        Needed = 1,
        PltRelSz = 2,
        PltGot = 3,
        Hash = 4,
        StrTab = 5,
        SymTab = 6,
        Rela = 7,
        RelaSz = 8,
        RelaEnt = 9,
        StrSz = 10,
        Syment = 11,
        Init = 12,
        Fini = 13,
        SoName = 14,
        RPath = 15,
        Symbolic = 16,
        Rel = 17,
        RelSz = 18,
        RelEnt = 19,
        PltRel = 20,
        Debug = 21,
        TextRel = 22,
        JmpRel = 23,
        BindNow = 24,
        InitArray = 25,
        FiniArray = 26,
        InitArraySz = 27,
        FiniArraySz = 28,
        RunPath = 29,
        Flags = 30,
        Encoding = 32,
        PreInitArray = 32,
        PreInitArraySz = 33,
        MaxPost = 34,

        // GNU Specific
        GnuHash = 0x6ffffef5,
        VerSym = 0x6ffffff0,
        RelaCount = 0x6ffffff9,
        RelCount = 0x6ffffffa,
        Flags1 = 0x6ffffffb,
        VerDef = 0x6ffffffc,
        VerDefNum = 0x6ffffffd,
        VerNeed = 0x6ffffffe,
        VerNeedNum = 0x6fffffff
    };

}
