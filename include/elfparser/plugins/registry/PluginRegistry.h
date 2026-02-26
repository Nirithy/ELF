#pragma once

#include "elfparser/plugins/registry/IExtensionRegistry.h"
#include "elfparser/plugins/core/IPlugin.h"
#include "elfparser/plugins/extension/IExtension.h"
#include <vector>
#include <mutex>
#include <memory>
#include <algorithm>

namespace ElfParser::Plugins::Registry {

    /**
     * @brief Central registry for all plugins and extensions.
     */
    class PluginRegistry : public IExtensionRegistry {
    public:
        static PluginRegistry& GetInstance();

        void RegisterExtension(std::shared_ptr<ElfParser::Plugins::Extensions::IExtension> extension) override;

        /**
         * @brief Register a plugin.
         * @param plugin The plugin to register.
         */
        void RegisterPlugin(std::shared_ptr<ElfParser::Plugins::IPlugin> plugin);

        /**
         * @brief Get all registered plugins.
         */
        const std::vector<std::shared_ptr<ElfParser::Plugins::IPlugin>>& GetPlugins() const;

        /**
         * @brief Get extensions by type.
         */
        template <typename T>
        std::vector<std::shared_ptr<T>> GetExtensions() const {
            std::vector<std::shared_ptr<T>> result;
            std::lock_guard<std::mutex> lock(m_mutex);
            for (const auto& ext : m_extensions) {
                if (auto casted = std::dynamic_pointer_cast<T>(ext)) {
                    result.push_back(casted);
                }
            }
            return result;
        }

    private:
        PluginRegistry() = default;
        ~PluginRegistry() = default;

        std::vector<std::shared_ptr<ElfParser::Plugins::IPlugin>> m_plugins;
        std::vector<std::shared_ptr<ElfParser::Plugins::Extensions::IExtension>> m_extensions;
        mutable std::mutex m_mutex;
    };

}
