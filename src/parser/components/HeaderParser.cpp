#include "elfparser/parser/components/HeaderParser.h"
#include "elfparser/utils/Logger.h"
#include "elfparser/utils/ElfSwap.h"
#include <cstring>
#include <vector>

namespace ElfParser::Parser::Components {

    Common::Result HeaderParser::Parse(IO::BinaryReader& reader, Model::Elf64_Ehdr& header) {
        // Read the first 16 bytes (e_ident) to determine endianness
        std::vector<unsigned char> ident(16);
        if (!reader.Read(ident.data(), 16)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read ELF identification");
        }

        // Validate Magic
        if (std::memcmp(ident.data(), Model::ELFMAG, Model::SELFMAG) != 0) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid ELF Magic");
        }

        // Check Class (Only 64-bit supported for now)
        // EI_CLASS is at index 4
        if (static_cast<Model::ElfClass>(ident[4]) != Model::ElfClass::Elf64) {
            return Common::Result::Fail(Common::StatusCode::NotImplemented, "Only ELF64 is supported.");
        }

        // Check Data Encoding (Endianness)
        // EI_DATA is at index 5
        auto dataEncoding = static_cast<Model::ElfData>(ident[5]);
        if (dataEncoding == Model::ElfData::Lsb) {
            reader.SetLittleEndian(true);
        } else if (dataEncoding == Model::ElfData::Msb) {
            reader.SetLittleEndian(false);
        } else {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid Data Encoding");
        }

        // Seek back to start and read the full header using the correct endianness
        reader.Seek(0);
        if (!reader.Read(header)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read full ELF Header");
        }

        if (reader.ShouldSwap()) {
            Utils::Swap(header);
        }

        return Common::Result::Ok();
    }

}
