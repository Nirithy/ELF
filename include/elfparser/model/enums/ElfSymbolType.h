#pragma once

#include <cstdint>

namespace ElfParser::Model {

    enum class ElfSymbolType : unsigned char {
        NoType = 0,
        Object = 1,
        Func = 2,
        Section = 3,
        File = 4,
        Common = 5,
        Tls = 6,
        LoOs = 10,
        HiOs = 12,
        LoProc = 13,
        HiProc = 15
    };

}
