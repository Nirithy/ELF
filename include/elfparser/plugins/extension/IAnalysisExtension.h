#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include <string>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for analyzing ELF files.
     */
    class IAnalysisExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "AnalysisExtension"; }

        /**
         * @brief Analyze the current state of the ELF file.
         * @return A string description of the analysis result.
         */
        virtual std::string Analyze() = 0;
    };

}
