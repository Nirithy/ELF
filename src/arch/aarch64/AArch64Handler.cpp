#include "elfparser/arch/aarch64/AArch64Handler.h"
#include <string>

namespace ElfParser::Arch {

    std::string AArch64Handler::GetRelocationString(uint32_t type) const {
        switch (type) {
            case 0: return "R_AARCH64_NONE";
            case 257: return "R_AARCH64_ABS64";
            case 258: return "R_AARCH64_ABS32";
            case 259: return "R_AARCH64_ABS16";
            case 260: return "R_AARCH64_PREL64";
            case 261: return "R_AARCH64_PREL32";
            case 262: return "R_AARCH64_PREL16";
            case 263: return "R_AARCH64_MOVW_UABS_G0";
            case 264: return "R_AARCH64_MOVW_UABS_G0_NC";
            case 265: return "R_AARCH64_MOVW_UABS_G1";
            case 266: return "R_AARCH64_MOVW_UABS_G1_NC";
            case 267: return "R_AARCH64_MOVW_UABS_G2";
            case 268: return "R_AARCH64_MOVW_UABS_G2_NC";
            case 269: return "R_AARCH64_MOVW_UABS_G3";
            case 270: return "R_AARCH64_MOVW_SABS_G0";
            case 271: return "R_AARCH64_MOVW_SABS_G1";
            case 272: return "R_AARCH64_MOVW_SABS_G2";
            case 1024: return "R_AARCH64_COPY";
            case 1025: return "R_AARCH64_GLOB_DAT";
            case 1026: return "R_AARCH64_JUMP_SLOT";
            case 1027: return "R_AARCH64_RELATIVE";
            case 1028: return "R_AARCH64_TLS_DTPMOD64";
            case 1029: return "R_AARCH64_TLS_DTPREL64";
            case 1030: return "R_AARCH64_TLS_TPREL64";
            default: return "Unknown (" + std::to_string(type) + ")";
        }
    }

    bool AArch64Handler::IsRelocationValid(uint32_t type) const {
        return type <= 1030; // Simplified range
    }

}
