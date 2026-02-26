#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class INote;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Notes.
     */
    class INoteAPI {
    public:
        virtual ~INoteAPI() = default;

        /**
         * @brief Get notes from a specific section.
         */
        virtual std::vector<Interface::INote*> GetNotes(const std::string& sectionName) = 0;

        /**
         * @brief Add a note to a section.
         */
        virtual Interface::INote* AddNote(const std::string& sectionName, const std::string& name, uint32_t type, const std::vector<uint8_t>& desc) = 0;
    };

}
