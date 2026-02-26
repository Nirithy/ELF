#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfVersion : uint8_t {
        None = 0,
        Current = 1
    };
}
