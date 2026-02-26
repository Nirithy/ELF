#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    struct NoteEntry {
        uint32_t type;
        std::string name;
        std::vector<uint8_t> description;
    };

    class NoteSectionBuilder : public SectionBuilder {
    public:
        explicit NoteSectionBuilder(const std::string& name = ".note.ABI-tag");

        void AddNote(uint32_t type, const std::string& name, const std::vector<uint8_t>& description);

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        std::vector<NoteEntry> m_notes;
    };

}
