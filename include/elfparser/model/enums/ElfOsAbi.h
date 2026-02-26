#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfOsAbi : uint8_t {
        SystemV = 0,
        HpUx = 1,
        NetBSD = 2,
        Linux = 3,
        Solaris = 6,
        Standalone = 255
    };
}
