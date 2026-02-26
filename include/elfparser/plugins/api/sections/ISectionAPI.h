#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class ISection;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Sections.
     */
    class ISectionAPI {
    public:
        virtual ~ISectionAPI() = default;

        /**
         * @brief Get a section by name.
         */
        virtual Interface::ISection* GetSection(const std::string& name) = 0;

        /**
         * @brief Get a section by index.
         */
        virtual Interface::ISection* GetSection(uint32_t index) = 0;

        /**
         * @brief Get all sections.
         */
        virtual std::vector<Interface::ISection*> GetAllSections() = 0;

        /**
         * @brief Create a new section.
         */
        virtual Interface::ISection* CreateSection(const std::string& name, uint32_t type) = 0;

        /**
         * @brief Remove a section.
         */
        virtual Common::Result RemoveSection(const std::string& name) = 0;
    };

}
