#pragma once

#include "elfparser/builder/ElfBuilder.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Transform {

    /**
     * @brief Interface for transformation actions that modify the ELF structure.
     */
    class ITransformation {
    public:
        virtual ~ITransformation() = default;

        /**
         * @brief Apply the transformation to the ELF builder.
         * @param builder The builder containing the current ELF state.
         * @return Result indicating success or failure.
         */
        virtual Common::Result Apply(Builder::ElfBuilder& builder) = 0;
    };

}
