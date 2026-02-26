#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class IVersionDefinition;
    class IVersionRequirement;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Versioning.
     */
    class IVersionAPI {
    public:
        virtual ~IVersionAPI() = default;

        /**
         * @brief Get version definitions.
         */
        virtual std::vector<Interface::IVersionDefinition*> GetVersionDefinitions() = 0;

        /**
         * @brief Get version requirements.
         */
        virtual std::vector<Interface::IVersionRequirement*> GetVersionRequirements() = 0;
    };

}
