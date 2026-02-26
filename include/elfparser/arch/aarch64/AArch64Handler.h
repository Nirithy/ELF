#pragma once

#include "elfparser/arch/IArchHandler.h"
#include "elfparser/model/enums/ElfMachine.h"

namespace ElfParser::Arch {

    class AArch64Handler : public IArchHandler {
    public:
        Model::ElfMachine GetMachineType() const override {
            return Model::ElfMachine::AArch64;
        }

        std::string GetRelocationString(uint32_t type) const override;
        bool IsRelocationValid(uint32_t type) const override;
    };

}
