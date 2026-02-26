#include "elfparser/parser/ElfParser.h"
#include "elfparser/utils/Logger.h"
#include <cstring>
#include <iostream>

namespace ElfParser::Parser {

    ElfParser::ElfParser(const std::string& filepath)
        : m_filepath(filepath), m_reader(std::make_unique<IO::BinaryReader>(filepath)) {
    }

    ElfParser::~ElfParser() = default;

    Common::Result ElfParser::Parse() {
        if (!m_reader->Open()) {
            return Common::Result::Fail(Common::StatusCode::FileNotFound, "Could not open file: " + m_filepath);
        }

        Utils::Logger::Info("Parsing ELF file: " + m_filepath);

        auto res = ValidateHeader();
        if (!res.IsOk()) return res;

        res = ReadProgramHeaders();
        if (!res.IsOk()) return res;

        res = ReadSectionHeaders();
        if (!res.IsOk()) return res;

        res = ReadSectionNames();
        if (!res.IsOk()) return res;

        Utils::Logger::Info("Successfully parsed ELF file.");
        return Common::Result::Ok();
    }

    Common::Result ElfParser::ValidateHeader() {
        if (!m_reader->Read(m_header)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read ELF Header");
        }

        // Check Magic
        if (std::memcmp(m_header.e_ident, Model::ELFMAG, Model::SELFMAG) != 0) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid ELF Magic");
        }

        // Check Class (Only 64-bit for now)
        // e_ident[4] is EI_CLASS
        if (static_cast<Model::ElfClass>(m_header.e_ident[4]) != Model::ElfClass::Elf64) {
             return Common::Result::Fail(Common::StatusCode::NotImplemented, "Only ELF64 is supported currently.");
        }

        return Common::Result::Ok();
    }

    Common::Result ElfParser::ReadProgramHeaders() {
        if (m_header.e_phoff == 0 || m_header.e_phnum == 0) return Common::Result::Ok();

        if (!m_reader->Seek(m_header.e_phoff)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Program Headers");
        }

        m_phdrs.resize(m_header.e_phnum);
        for (int i = 0; i < m_header.e_phnum; ++i) {
             if (!m_reader->Read(m_phdrs[i])) {
                  return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Program Header " + std::to_string(i));
             }
        }
        return Common::Result::Ok();
    }

    Common::Result ElfParser::ReadSectionHeaders() {
        if (m_header.e_shoff == 0 || m_header.e_shnum == 0) return Common::Result::Ok();

        if (!m_reader->Seek(m_header.e_shoff)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Section Headers");
        }

        m_shdrs.resize(m_header.e_shnum);
        for (int i = 0; i < m_header.e_shnum; ++i) {
             if (!m_reader->Read(m_shdrs[i])) {
                  return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Section Header " + std::to_string(i));
             }
        }
        return Common::Result::Ok();
    }

    Common::Result ElfParser::ReadSectionNames() {
        // e_shstrndx is the index of the section header table entry that contains the section names.
        if (m_header.e_shstrndx == 0 || m_header.e_shstrndx >= m_header.e_shnum) {
            // No string table or invalid index (SHN_UNDEF is 0)
            return Common::Result::Ok();
        }

        const auto& shstrtab_hdr = m_shdrs[m_header.e_shstrndx];
        m_shstrtab.resize(shstrtab_hdr.sh_size);

        if (!m_reader->Seek(shstrtab_hdr.sh_offset)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to SH String Table");
        }

        if (!m_reader->Read(m_shstrtab.data(), shstrtab_hdr.sh_size)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read SH String Table");
        }

        return Common::Result::Ok();
    }

    std::string ElfParser::GetSectionName(uint32_t offset) const {
        if (offset >= m_shstrtab.size()) return "";
        // Read until null terminator safely
        size_t len = 0;
        for (size_t i = offset; i < m_shstrtab.size(); ++i) {
            if (m_shstrtab[i] == '\0') break;
            len++;
        }
        return std::string(&m_shstrtab[offset], len);
    }

}
