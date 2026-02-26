#pragma once

#include <memory>
#include "elfparser/arch/IArchHandler.h"
#include "elfparser/model/enums/ElfMachine.h"

namespace ElfParser::Arch {

    class ArchFactory {
    public:
        /**
         * @brief Creates an architecture handler for the specified machine type.
         * @param machine The ELF machine type.
         * @return A unique pointer to the handler, or nullptr if not supported.
         */
        static std::unique_ptr<IArchHandler> CreateHandler(Model::ElfMachine machine);
    };

}
