#include "elfparser/builder/components/sections/notes/NoteSectionBuilder.h"
#include "elfparser/io/BinaryWriter.h"

namespace ElfParser::Builder::Components {

    NoteSectionBuilder::NoteSectionBuilder(const std::string& name) : SectionBuilder() {
        SetName(name);
        SetType(Model::ElfSectionType::Note);
        SetEntSize(0);
        SetAddralign(4);
    }

    void NoteSectionBuilder::AddNote(uint32_t type, const std::string& name, const std::vector<uint8_t>& description) {
        m_notes.push_back({type, name, description});
    }

    Common::Result NoteSectionBuilder::Write(IO::BinaryWriter& writer) {
        for (const auto& note : m_notes) {
            uint32_t namesz = static_cast<uint32_t>(note.name.size() + 1); // +1 for null terminator
            uint32_t descsz = static_cast<uint32_t>(note.description.size());
            uint32_t type = note.type;

            auto res = writer.Write(namesz);
            if (!res.IsOk()) return res;

            res = writer.Write(descsz);
            if (!res.IsOk()) return res;

            res = writer.Write(type);
            if (!res.IsOk()) return res;

            // Write name with null terminator
            res = writer.Write(note.name.c_str(), namesz);
            if (!res.IsOk()) return res;

            // Padding for name
            uint32_t namePad = (4 - (namesz % 4)) % 4;
            if (namePad > 0) {
                res = writer.WritePadding(namePad);
                if (!res.IsOk()) return res;
            }

            // Write description
            if (descsz > 0) {
                res = writer.Write(note.description.data(), descsz);
                if (!res.IsOk()) return res;

                // Padding for description
                uint32_t descPad = (4 - (descsz % 4)) % 4;
                if (descPad > 0) {
                    res = writer.WritePadding(descPad);
                    if (!res.IsOk()) return res;
                }
            }
        }
        return Common::Result::Ok();
    }

    uint64_t NoteSectionBuilder::GetSize() const {
        uint64_t size = 0;
        for (const auto& note : m_notes) {
            size += 12; // 3 * 4 bytes header

            uint32_t namesz = static_cast<uint32_t>(note.name.size() + 1);
            uint32_t namePad = (4 - (namesz % 4)) % 4;
            size += namesz + namePad;

            uint32_t descsz = static_cast<uint32_t>(note.description.size());
            uint32_t descPad = (4 - (descsz % 4)) % 4;
            size += descsz + descPad;
        }
        return size;
    }

}
