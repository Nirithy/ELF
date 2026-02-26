#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfSegmentType : uint32_t {
        Null = 0,
        Load = 1,
        Dynamic = 2,
        Interp = 3,
        Note = 4,
        ShLib = 5,
        Phdr = 6,
        Tls = 7
    };
}
