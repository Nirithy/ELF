#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfType : uint16_t {
        None = 0,
        Rel = 1,
        Exec = 2,
        Dyn = 3,
        Core = 4
    };
}
