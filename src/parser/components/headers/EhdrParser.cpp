#include "elfparser/parser/components/headers/EhdrParser.h"
#include "elfparser/utils/Logger.h"
#include "elfparser/utils/ElfSwap.h"
#include <cstring>
#include <vector>

namespace ElfParser::Parser::Components {

    Common::Result EhdrParser::Parse(IO::BinaryReader& reader, Model::Elf64_Ehdr& header) {
        // Read the first 16 bytes (e_ident) to determine endianness
        std::vector<unsigned char> ident(16);
        if (!reader.Read(ident.data(), 16)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read ELF identification");
        }

        // Validate Magic
        if (std::memcmp(ident.data(), Model::ELFMAG, Model::SELFMAG) != 0) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid ELF Magic");
        }

        // Check Data Encoding (Endianness)
        auto dataEncoding = static_cast<Model::ElfData>(ident[5]);
        if (dataEncoding == Model::ElfData::Lsb) {
            reader.SetLittleEndian(true);
        } else if (dataEncoding == Model::ElfData::Msb) {
            reader.SetLittleEndian(false);
        } else {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid Data Encoding");
        }

        // Check Class
        auto elfClass = static_cast<Model::ElfClass>(ident[4]);

        // Seek back to start
        reader.Seek(0);

        if (elfClass == Model::ElfClass::Elf64) {
             if (!reader.Read(header)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read full ELF Header");
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(header);
            }
        } else if (elfClass == Model::ElfClass::Elf32) {
             Model::Elf32_Ehdr header32;
             if (!reader.Read(header32)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read 32-bit ELF Header");
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(header32);
            }

            // Convert to 64-bit
            std::memcpy(header.e_ident, header32.e_ident, 16);
            header.e_type = header32.e_type;
            header.e_machine = header32.e_machine;
            header.e_version = header32.e_version;
            header.e_entry = header32.e_entry;
            header.e_phoff = header32.e_phoff;
            header.e_shoff = header32.e_shoff;
            header.e_flags = header32.e_flags;
            header.e_ehsize = header32.e_ehsize;
            header.e_phentsize = header32.e_phentsize;
            header.e_phnum = header32.e_phnum;
            header.e_shentsize = header32.e_shentsize;
            header.e_shnum = header32.e_shnum;
            header.e_shstrndx = header32.e_shstrndx;
        } else {
             return Common::Result::Fail(Common::StatusCode::NotImplemented, "Unknown ELF Class");
        }

        return Common::Result::Ok();
    }
}
