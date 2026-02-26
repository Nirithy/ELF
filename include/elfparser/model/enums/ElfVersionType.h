#pragma once

#include <cstdint>

namespace ElfParser::Model {

    // Helper enums for Versioning structures

    // VerDef flags
    enum class ElfVerDefFlags : uint16_t {
        None = 0,
        Base = 1,
        Weak = 2
    };

    // VerNeed flags
    enum class ElfVerNeedFlags : uint16_t {
        None = 0,
        Weak = 2
    };

    // Versym
    enum class ElfVerSymHidden : uint16_t {
        Hidden = 0x8000
    };

}
