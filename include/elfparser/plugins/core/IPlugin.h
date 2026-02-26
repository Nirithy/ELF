#pragma once

#include "elfparser/plugins/core/PluginInfo.h"
#include "elfparser/common/Types.h"
#include <memory>

namespace ElfParser::Plugins {

    class PluginContext;

    /**
     * @brief The base interface that all plugins must implement.
     */
    class IPlugin {
    public:
        virtual ~IPlugin() = default;

        /**
         * @brief Get the metadata for this plugin.
         */
        virtual const PluginInfo& GetInfo() const = 0;

        /**
         * @brief Initialize the plugin.
         * @param context The plugin context provided by the host.
         * @return Result indicating success or failure.
         */
        virtual Common::Result Initialize(PluginContext& context) = 0;

        /**
         * @brief Clean up the plugin resources.
         * @return Result indicating success or failure.
         */
        virtual Common::Result Shutdown() = 0;
    };

}
