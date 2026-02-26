#pragma once

#include <memory>
#include <string>
#include <vector>
#include "elfparser/interface/INote.h"

namespace ElfParser::Factory {

    class NoteFactory {
    public:
        /**
         * @brief Creates a new Note instance.
         * @param type The note type.
         * @param name The note name.
         * @param descriptor The note descriptor.
         * @return A unique pointer to the created note.
         */
        static std::unique_ptr<Interface::INote> CreateNote(
            uint32_t type,
            const std::string& name,
            const std::vector<unsigned char>& descriptor
        );
    };

}
