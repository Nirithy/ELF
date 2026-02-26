#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfMachine : uint16_t {
        None = 0,
        X86 = 3,
        MIPS = 8,
        PPC = 20,
        ARM = 40,
        X86_64 = 62,
        AArch64 = 183
    };
}
