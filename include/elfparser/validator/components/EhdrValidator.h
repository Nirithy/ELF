#pragma once

#include "elfparser/validator/IValidator.h"
#include "elfparser/model/structs/ElfEhdr.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Validator::Components {

    class EhdrValidator : public IValidator {
    public:
        std::string GetName() const override { return "EhdrValidator"; }

        /**
         * @brief Validates the ELF Header.
         * @param header The ELF header to validate.
         * @return Result indicating success or failure.
         */
        Common::Result Validate(const Model::Elf64_Ehdr& header);
    };

}
