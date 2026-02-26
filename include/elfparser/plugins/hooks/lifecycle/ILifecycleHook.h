#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Plugins::Hooks {

    class ILifecycleHook : public Extensions::IExtension {
    public:
        virtual ~ILifecycleHook() = default;

        virtual void OnPluginLoaded() = 0;
        virtual void OnPluginUnloaded() = 0;
    };
}
