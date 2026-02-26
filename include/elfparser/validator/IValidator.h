#pragma once

#include <string>
#include "elfparser/common/Types.h"

namespace ElfParser::Validator {

    /**
     * @brief Base interface for all validator components.
     */
    class IValidator {
    public:
        virtual ~IValidator() = default;

        /**
         * @brief Get the name of the validator.
         * @return The validator name.
         */
        virtual std::string GetName() const = 0;
    };

}
