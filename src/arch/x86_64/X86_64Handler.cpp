#include "elfparser/arch/x86_64/X86_64Handler.h"

namespace ElfParser::Arch {

    std::string X86_64Handler::GetRelocationString(uint32_t type) const {
        switch (type) {
            case 0: return "R_X86_64_NONE";
            case 1: return "R_X86_64_64";
            case 2: return "R_X86_64_PC32";
            case 3: return "R_X86_64_GOT32";
            case 4: return "R_X86_64_PLT32";
            case 5: return "R_X86_64_COPY";
            case 6: return "R_X86_64_GLOB_DAT";
            case 7: return "R_X86_64_JUMP_SLOT";
            case 8: return "R_X86_64_RELATIVE";
            case 9: return "R_X86_64_GOTPCREL";
            case 10: return "R_X86_64_32";
            case 11: return "R_X86_64_32S";
            case 12: return "R_X86_64_16";
            case 13: return "R_X86_64_PC16";
            case 14: return "R_X86_64_8";
            case 15: return "R_X86_64_PC8";
            case 16: return "R_X86_64_DTPMOD64";
            case 17: return "R_X86_64_DTPOFF64";
            case 18: return "R_X86_64_TPOFF64";
            case 19: return "R_X86_64_TLSGD";
            case 20: return "R_X86_64_TLSLD";
            case 21: return "R_X86_64_DTPOFF32";
            case 22: return "R_X86_64_GOTTPOFF";
            case 23: return "R_X86_64_TPOFF32";
            case 24: return "R_X86_64_PC64";
            case 25: return "R_X86_64_GOTOFF64";
            case 26: return "R_X86_64_GOTPC32";
            case 32: return "R_X86_64_SIZE32";
            case 33: return "R_X86_64_SIZE64";
            default: return "Unknown (" + std::to_string(type) + ")";
        }
    }

    bool X86_64Handler::IsRelocationValid(uint32_t type) const {
        // Simple check for now. The range is technically larger but this covers standard set.
        return type <= 42;
    }

}
