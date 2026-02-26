#pragma once

#include <cstdint>

namespace ElfParser::Model {

    enum class ElfSymbolBinding : unsigned char {
        Local = 0,
        Global = 1,
        Weak = 2,
        LoOs = 10,
        HiOs = 12,
        LoProc = 13,
        HiProc = 15
    };

}
