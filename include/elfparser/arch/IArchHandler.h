#pragma once

#include <string>
#include "elfparser/model/enums/ElfMachine.h"
#include "elfparser/model/structs/ElfRel.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Arch {

    /**
     * @brief Interface for architecture-specific handling logic.
     */
    class IArchHandler {
    public:
        virtual ~IArchHandler() = default;

        /**
         * @brief Get the machine type this handler supports.
         * @return The ElfMachine enum value.
         */
        virtual Model::ElfMachine GetMachineType() const = 0;

        /**
         * @brief Get the string representation of a relocation type.
         * @param type The raw relocation type (e.g., R_X86_64_NONE).
         * @return A string description of the relocation type.
         */
        virtual std::string GetRelocationString(uint32_t type) const = 0;

        /**
         * @brief Validate if a relocation type is supported/valid for this architecture.
         * @param type The raw relocation type.
         * @return True if valid, false otherwise.
         */
        virtual bool IsRelocationValid(uint32_t type) const = 0;
    };

}
