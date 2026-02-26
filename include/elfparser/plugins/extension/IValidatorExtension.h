#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for custom ELF validation rules.
     */
    class IValidatorExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "ValidatorExtension"; }

        /**
         * @brief Validate the ELF header.
         * @param header The ELF header.
         * @return Validation result.
         */
        virtual Common::Result ValidateHeader(const Model::Elf64_Ehdr& header) { return Common::Result::Ok(); }

        /**
         * @brief Validate a section header.
         * @param shdr The section header.
         * @return Validation result.
         */
        virtual Common::Result ValidateSection(const Model::Elf64_Shdr& shdr) { return Common::Result::Ok(); }
    };

}
