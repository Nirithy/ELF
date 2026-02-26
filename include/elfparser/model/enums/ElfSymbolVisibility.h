#pragma once

#include <cstdint>

namespace ElfParser::Model {

    enum class ElfSymbolVisibility : unsigned char {
        Default = 0,
        Internal = 1,
        Hidden = 2,
        Protected = 3
    };

}
