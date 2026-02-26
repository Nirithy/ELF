#include "elfparser/plugins/registry/PluginRegistry.h"

namespace ElfParser::Plugins::Registry {

    PluginRegistry& PluginRegistry::GetInstance() {
        static PluginRegistry instance;
        return instance;
    }

    void PluginRegistry::RegisterExtension(std::shared_ptr<ElfParser::Plugins::Extensions::IExtension> extension) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (extension) {
            m_extensions.push_back(extension);
        }
    }

    void PluginRegistry::RegisterPlugin(std::shared_ptr<ElfParser::Plugins::IPlugin> plugin) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (plugin) {
            m_plugins.push_back(plugin);
        }
    }

    const std::vector<std::shared_ptr<ElfParser::Plugins::IPlugin>>& PluginRegistry::GetPlugins() const {
        return m_plugins;
    }

}
