#pragma once

#include "elfparser/plugins/loaders/IPluginLoader.h"
#include <vector>
#include <memory>

namespace ElfParser::Plugins::Loaders {

    /**
     * @brief Loader for statically linked plugins.
     * This loader is useful when dynamic loading is not available or desired.
     */
    class StaticPluginLoader : public IPluginLoader {
    public:
        StaticPluginLoader() = default;
        ~StaticPluginLoader() = default;

        Common::Result Load() override;
    };

}
