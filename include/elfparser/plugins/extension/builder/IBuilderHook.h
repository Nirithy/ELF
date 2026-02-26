#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"
#include <cstdint>

namespace ElfParser::Interface {
    class ISection;
}

namespace ElfParser::Plugins::Extensions {

    class IBuilderHook : public IExtension {
    public:
        virtual ~IBuilderHook() = default;

        virtual void OnLayoutCalculated(uint64_t totalSize) = 0;
        virtual void OnSectionWritten(const Interface::ISection* section, uint64_t offset) = 0;
    };
}
