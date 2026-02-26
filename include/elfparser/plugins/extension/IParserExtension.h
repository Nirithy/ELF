#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include <vector>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for customizing the parsing process.
     */
    class IParserExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "ParserExtension"; }

        /**
         * @brief Called before parsing begins.
         * @param filepath The path to the ELF file.
         */
        virtual void OnPreParse(const std::string& filepath) {}

        /**
         * @brief Called after parsing completes successfully.
         * @param header The parsed ELF header.
         */
        virtual void OnPostParse(const Model::Elf64_Ehdr& header) {}

        /**
         * @brief Called when a section is encountered.
         * @param shdr The section header.
         * @return True to continue default processing, false to skip.
         */
        virtual bool OnSectionParse(const Model::Elf64_Shdr& shdr) { return true; }
    };

}
