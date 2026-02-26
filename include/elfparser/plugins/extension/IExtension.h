#pragma once

#include <string>

namespace ElfParser::Plugins::Extensions {

    /**
     * @brief Base interface for all extension points.
     */
    class IExtension {
    public:
        virtual ~IExtension() = default;

        /**
         * @brief Get the type of extension.
         */
        virtual std::string GetExtensionType() const = 0;
    };

}
