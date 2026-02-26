#pragma once

#include "elfparser/validator/IValidator.h"
#include "elfparser/model/structs/ElfShdr.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Validator::Components {

    class ShdrValidator : public IValidator {
    public:
        std::string GetName() const override { return "ShdrValidator"; }

        /**
         * @brief Validates a Section Header.
         * @param header The section header.
         * @return Result.
         */
        Common::Result Validate(const Model::Elf64_Shdr& header);
    };

}
