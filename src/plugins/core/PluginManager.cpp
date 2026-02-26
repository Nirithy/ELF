#include "elfparser/plugins/core/PluginManager.h"
#include "elfparser/plugins/events/EventDispatcher.h"
#include "elfparser/plugins/core/PluginContext.h"
#include "elfparser/plugins/events/EventTypes.h"
#include "elfparser/plugins/events/Event.h"

namespace ElfParser::Plugins {

    PluginManager::PluginManager()
        : m_eventDispatcher(std::make_shared<Events::EventDispatcher>())
        , m_context(std::make_unique<PluginContext>(m_eventDispatcher))
    {
    }

    PluginManager::~PluginManager() {
        ShutdownPlugins();
    }

    Common::Result PluginManager::Initialize() {
        m_initialized = true;
        return Common::Result::Ok();
    }

    Common::Result PluginManager::RegisterPlugin(std::unique_ptr<IPlugin> plugin) {
        if (!plugin) {
            return Common::Result::Fail(Common::StatusCode::Error, "Plugin cannot be null");
        }

        m_plugins.push_back(std::move(plugin));
        return Common::Result::Ok();
    }

    Common::Result PluginManager::InitializePlugins() {
        if (!m_initialized) {
            return Common::Result::Fail(Common::StatusCode::Error, "PluginManager not initialized");
        }

        for (auto& plugin : m_plugins) {
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

        for (auto it = m_plugins.rbegin(); it != m_plugins.rend(); ++it) {
            auto& plugin = *it;
            plugin->Shutdown();

            // Dispatch event
            m_eventDispatcher->Dispatch(Events::Event(Events::EventType::PluginUnloaded, plugin->GetInfo().name));
        }

        m_plugins.clear();
        m_initialized = false;
        return Common::Result::Ok();
    }

    IPlugin* PluginManager::GetPlugin(const std::string& name) {
        for (const auto& plugin : m_plugins) {
            if (plugin->GetInfo().name == name) {
                return plugin.get();
            }
        }
        return nullptr;
    }

}
