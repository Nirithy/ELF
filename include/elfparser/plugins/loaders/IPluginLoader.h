#pragma once

#include "elfparser/common/Types.h"
#include <string>

namespace ElfParser::Plugins::Loaders {

    /**
     * @brief Interface for loading plugins.
     */
    class IPluginLoader {
    public:
        virtual ~IPluginLoader() = default;

        /**
         * @brief Load plugins from a source (e.g., path, configuration).
         * @return Result indicating success or failure.
         */
        virtual Common::Result Load() = 0;
    };

}
