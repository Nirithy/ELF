#include "elfparser/plugins/core/PluginManager.h"
#include "elfparser/plugins/events/EventDispatcher.h"
#include "elfparser/plugins/core/PluginContext.h"
#include "elfparser/plugins/events/EventTypes.h"
#include "elfparser/plugins/events/Event.h"
#include "elfparser/plugins/registry/PluginRegistry.h"

namespace ElfParser::Plugins {

    PluginManager::PluginManager()
        : m_eventDispatcher(std::make_shared<Events::EventDispatcher>())
        , m_context(std::make_unique<PluginContext>(m_eventDispatcher))
        , m_staticLoader(std::make_unique<Loaders::StaticPluginLoader>())
    {
    }

    PluginManager::~PluginManager() {
        ShutdownPlugins();
    }

    Common::Result PluginManager::Initialize() {
        m_initialized = true;
        // Load static plugins
        m_staticLoader->Load();
        return Common::Result::Ok();
    }

    Common::Result PluginManager::RegisterPlugin(std::shared_ptr<IPlugin> plugin) {
        if (!plugin) {
            return Common::Result::Fail(Common::StatusCode::Error, "Plugin cannot be null");
        }

        Registry::PluginRegistry::GetInstance().RegisterPlugin(plugin);
        return Common::Result::Ok();
    }

    Common::Result PluginManager::InitializePlugins() {
        if (!m_initialized) {
            return Common::Result::Fail(Common::StatusCode::Error, "PluginManager not initialized");
        }

        const auto& plugins = Registry::PluginRegistry::GetInstance().GetPlugins();
        for (auto& plugin : plugins) {
            auto result = plugin->Initialize(*m_context);
            if (!result.IsOk()) {
                // Log error but continue initializing other plugins? Or fail?
                // For now, return failure.
                return result;
            }

            // Dispatch event
            m_eventDispatcher->Dispatch(Events::Event(Events::EventType::PluginLoaded, plugin->GetInfo().name));
        }

        return Common::Result::Ok();
    }

    Common::Result PluginManager::ShutdownPlugins() {
        if (!m_initialized) {
            return Common::Result::Ok();
        }

        const auto& plugins = Registry::PluginRegistry::GetInstance().GetPlugins();
        // Shutdown in reverse order? The registry returns a reference to vector, we can iterate reverse.
        // However, standard iteration is easiest. If dependencies exist, reverse might be needed.
        // Let's copy to vector to reverse iterate safely if needed, or just reverse iterator.

        for (auto it = plugins.rbegin(); it != plugins.rend(); ++it) {
            auto& plugin = *it;
            plugin->Shutdown();

            // Dispatch event
            m_eventDispatcher->Dispatch(Events::Event(Events::EventType::PluginUnloaded, plugin->GetInfo().name));
        }

        // We don't clear the registry here because PluginManager doesn't own the registry.
        // But maybe we should? The registry is a singleton.
        // If we want to fully reset, we might need a Clear() method on Registry.
        // For now, just shutting down plugins is enough.

        m_initialized = false;
        return Common::Result::Ok();
    }

    IPlugin* PluginManager::GetPlugin(const std::string& name) {
        const auto& plugins = Registry::PluginRegistry::GetInstance().GetPlugins();
        for (const auto& plugin : plugins) {
            if (plugin->GetInfo().name == name) {
                return plugin.get();
            }
        }
        return nullptr;
    }

}
