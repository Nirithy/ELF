#include "elfparser/parser/components/sections/notes/NoteSectionParser.h"
#include "elfparser/utils/Logger.h"
#include "elfparser/utils/ElfSwap.h"
#include <iostream>

namespace ElfParser::Parser::Components {

    Common::Result NoteSectionParser::Parse(IO::BinaryReader& reader,
                                            const Model::Elf64_Ehdr& ehdr,
                                            const Model::Elf64_Shdr& shdr,
                                            std::vector<ElfNoteEntry>& notes) {

        if (!reader.Seek(shdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to note section offset");
        }

        uint64_t endOffset = shdr.sh_offset + shdr.sh_size;

        // Use sh_addralign for alignment if present, otherwise default to 4 bytes.
        uint64_t alignment = (shdr.sh_addralign > 0) ? shdr.sh_addralign : 4;

        while (reader.Tell() < endOffset) {
            Model::Elf64_Nhdr nhdr;

            // Nhdr is always 12 bytes: 3 uint32_t.
            if (!reader.Read(nhdr)) {
                 return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Note Header");
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(nhdr);
            }

            ElfNoteEntry entry;
            entry.type = nhdr.n_type;

            // Calculate padding helper
            auto pad = [alignment](uint64_t size) -> uint64_t {
                return (alignment - (size % alignment)) % alignment;
            };

            // Read Name
            if (nhdr.n_namesz > 0) {
                std::vector<char> nameBuf(nhdr.n_namesz);
                if (!reader.Read(nameBuf.data(), nhdr.n_namesz)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Note Name");
                }

                // Usually name is null terminated, but n_namesz includes it.
                // We convert to std::string safely.
                if (nameBuf.back() == '\0') {
                    entry.name = std::string(nameBuf.data());
                } else {
                    entry.name = std::string(nameBuf.begin(), nameBuf.end());
                }

                // Skip padding for name
                uint64_t padding = pad(nhdr.n_namesz);
                reader.Seek(reader.Tell() + (std::streamoff)padding);
            }

            // Read Descriptor
            if (nhdr.n_descsz > 0) {
                entry.descriptor.resize(nhdr.n_descsz);
                if (!reader.Read(entry.descriptor.data(), nhdr.n_descsz)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Note Descriptor");
                }

                // Skip padding for descriptor
                uint64_t padding = pad(nhdr.n_descsz);
                reader.Seek(reader.Tell() + (std::streamoff)padding);
            }

            notes.push_back(entry);

            // Ensure we are aligned for the next note (some implementations align note start too)
            // But usually alignment happens per field (name, desc).
            // Let's assume the previous padding handled it correctly.
        }

        return Common::Result::Ok();
    }
}
