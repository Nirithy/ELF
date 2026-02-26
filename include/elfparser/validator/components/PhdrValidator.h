#pragma once

#include "elfparser/validator/IValidator.h"
#include "elfparser/model/structs/ElfPhdr.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Validator::Components {

    class PhdrValidator : public IValidator {
    public:
        std::string GetName() const override { return "PhdrValidator"; }

        /**
         * @brief Validates a Program Header.
         * @param header The program header.
         * @return Result.
         */
        Common::Result Validate(const Model::Elf64_Phdr& header);
    };

}
