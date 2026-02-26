#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/model/ElfStructures.h"
#include <string>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for customizing the build process.
     */
    class IBuilderExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "BuilderExtension"; }

        /**
         * @brief Called before layout calculation.
         */
        virtual void OnPreBuild(const std::string& outputPath) {}

        /**
         * @brief Called after layout calculation but before writing.
         */
        virtual void OnPostLayout(const Model::Elf64_Ehdr& header) {}

        /**
         * @brief Called after writing is complete.
         */
        virtual void OnPostBuild(const std::string& outputPath) {}
    };

}
