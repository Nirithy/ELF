#pragma once
#include <cstdint>

namespace ElfParser::Model {
    enum class ElfClass : uint8_t {
        None = 0,
        Elf32 = 1,
        Elf64 = 2
    };
}
