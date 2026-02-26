#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/model/ElfStructures.h"
#include <string>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Extension point for read-only analysis of the ELF file.
     */
    class IAnalysisExtension : public IExtension {
    public:
        std::string GetExtensionType() const override { return "AnalysisExtension"; }

        /**
         * @brief Perform analysis on the parsed ELF structure.
         * @return Analysis report as a string (or JSON).
         */
        virtual std::string Analyze() = 0;
    };

}
