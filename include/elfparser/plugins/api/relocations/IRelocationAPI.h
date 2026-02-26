#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class IRelocation;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Relocations.
     */
    class IRelocationAPI {
    public:
        virtual ~IRelocationAPI() = default;

        /**
         * @brief Get relocations for a specific section.
         */
        virtual std::vector<Interface::IRelocation*> GetRelocations(const std::string& sectionName) = 0;

        /**
         * @brief Add a relocation to a section.
         */
        virtual Interface::IRelocation* AddRelocation(const std::string& sectionName, uint64_t offset, uint32_t type, const std::string& symbolName) = 0;
    };

}
