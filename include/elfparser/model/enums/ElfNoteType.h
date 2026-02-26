#pragma once

#include <cstdint>

namespace ElfParser::Model {

    enum class ElfNoteType : uint32_t {
        // Core dump note types
        PrStatus = 1,
        PrFpreg = 2,
        PrPsinfo = 3,
        PrTaskstruct = 4,
        PrAuxv = 6,

        // GNU note types
        GnuAbiTag = 1,
        GnuHwCap = 2,
        GnuBuildId = 3,
        GnuGoldVersion = 4,
        GnuPropertyType0 = 5,

        // Go note types
        GoBuildId = 4
    };

}
