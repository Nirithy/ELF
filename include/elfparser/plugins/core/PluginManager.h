#pragma once

#include <vector>
#include <memory>
#include <string>
#include "elfparser/plugins/core/IPlugin.h"
#include "elfparser/plugins/core/PluginContext.h"
#include "elfparser/common/Types.h"
#include "elfparser/plugins/events/EventDispatcher.h"
#include "elfparser/plugins/registry/PluginRegistry.h"
#include "elfparser/plugins/loaders/StaticPluginLoader.h"

namespace ElfParser::Plugins {

    class PluginManager {
    public:
        PluginManager();
        ~PluginManager();

        /**
         * @brief Initialize the plugin manager.
         * @return Result indicating success or failure.
         */
        Common::Result Initialize();

        /**
         * @brief Register a plugin instance.
         * @param plugin The plugin instance.
         * @return Result indicating success or failure.
         */
        Common::Result RegisterPlugin(std::shared_ptr<IPlugin> plugin);

        /**
         * @brief Initialize all registered plugins.
         */
        Common::Result InitializePlugins();

        /**
         * @brief Shutdown all plugins.
         */
        Common::Result ShutdownPlugins();

        /**
         * @brief Get a plugin by name.
         */
        IPlugin* GetPlugin(const std::string& name);

        /**
         * @brief Get the event dispatcher.
         */
        std::shared_ptr<Events::EventDispatcher> GetEventDispatcher() const { return m_eventDispatcher; }

    private:
        std::shared_ptr<Events::EventDispatcher> m_eventDispatcher;
        std::unique_ptr<PluginContext> m_context;
        std::unique_ptr<Loaders::StaticPluginLoader> m_staticLoader;
        bool m_initialized = false;
    };

}
