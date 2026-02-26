#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfData : uint8_t {
        None = 0,
        Lsb = 1, // Little Endian
        Msb = 2  // Big Endian
    };
}
