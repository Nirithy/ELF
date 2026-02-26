#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include <string>

namespace ElfParser::Plugins::Extensions {

    struct AnalysisResult {
        std::string Name;
        bool Passed;
        std::string Message;
    };

    class IAnalysisHook : public IExtension {
    public:
        virtual ~IAnalysisHook() = default;

        virtual AnalysisResult Analyze() = 0;
    };
}
