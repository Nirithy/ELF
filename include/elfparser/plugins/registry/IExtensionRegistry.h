#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include <memory>
#include <string>

namespace ElfParser::Plugins::Registry {

    /**
     * @brief Interface for registering extensions.
     */
    class IExtensionRegistry {
    public:
        virtual ~IExtensionRegistry() = default;

        /**
         * @brief Register an extension.
         * @param extension The extension to register.
         */
        virtual void RegisterExtension(std::shared_ptr<ElfParser::Plugins::Extensions::IExtension> extension) = 0;
    };

}
