#include "elfparser/arch/ArchFactory.h"
#include "elfparser/arch/x86_64/X86_64Handler.h"
#include "elfparser/arch/aarch64/AArch64Handler.h"
#include "elfparser/arch/riscv/RiscvHandler.h"

namespace ElfParser::Arch {

    std::unique_ptr<IArchHandler> ArchFactory::CreateHandler(Model::ElfMachine machine) {
        switch (machine) {
            case Model::ElfMachine::X86_64:
                return std::make_unique<X86_64Handler>();
            case Model::ElfMachine::AArch64:
                return std::make_unique<AArch64Handler>();
            case Model::ElfMachine::RISCV:
                return std::make_unique<RiscvHandler>();
            default:
                return nullptr;
        }
    }

}
