#pragma once

#include <memory>
#include "elfparser/interface/IVersionDefinition.h"
#include "elfparser/interface/IVersionRequirement.h"

namespace ElfParser::Factory {

    class VersionFactory {
    public:
        /**
         * @brief Creates a new Version Definition instance.
         * @return A unique pointer to the created version definition.
         */
        static std::unique_ptr<Interface::IVersionDefinition> CreateVersionDefinition();

        /**
         * @brief Creates a new Version Requirement instance.
         * @return A unique pointer to the created version requirement.
         */
        static std::unique_ptr<Interface::IVersionRequirement> CreateVersionRequirement();
    };

}
