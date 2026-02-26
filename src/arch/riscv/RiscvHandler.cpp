#include "elfparser/arch/riscv/RiscvHandler.h"
#include <string>

namespace ElfParser::Arch {

    std::string RiscvHandler::GetRelocationString(uint32_t type) const {
        switch (type) {
            case 0: return "R_RISCV_NONE";
            case 1: return "R_RISCV_32";
            case 2: return "R_RISCV_64";
            case 3: return "R_RISCV_RELATIVE";
            case 4: return "R_RISCV_COPY";
            case 5: return "R_RISCV_JUMP_SLOT";
            case 6: return "R_RISCV_TLS_DTPMOD32";
            case 7: return "R_RISCV_TLS_DTPMOD64";
            case 8: return "R_RISCV_TLS_DTPREL32";
            case 9: return "R_RISCV_TLS_DTPREL64";
            case 10: return "R_RISCV_TLS_TPREL32";
            case 11: return "R_RISCV_TLS_TPREL64";
            default: return "Unknown (" + std::to_string(type) + ")";
        }
    }

    bool RiscvHandler::IsRelocationValid(uint32_t type) const {
        // Simple check
        return type <= 11;
    }

}
