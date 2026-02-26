#include "elfparser/parser/components/SectionParser.h"
#include "elfparser/utils/ElfSwap.h"
#include <iostream>

namespace ElfParser::Parser::Components {

    Common::Result SectionParser::ParseHeaders(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, std::vector<Model::Elf64_Shdr>& sections) {
        if (header.e_shoff == 0 || header.e_shnum == 0) {
            sections.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(header.e_shoff)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Section Headers");
        }

        sections.resize(header.e_shnum);
        for (int i = 0; i < header.e_shnum; ++i) {
            if (!reader.Read(sections[i])) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Section Header " + std::to_string(i));
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(sections[i]);
            }
        }
        return Common::Result::Ok();
    }

    Common::Result SectionParser::ParseStringTable(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const std::vector<Model::Elf64_Shdr>& sections, std::vector<char>& strTab) {
        if (header.e_shstrndx == 0) {
             // SHN_UNDEF is 0. If it's 0, there's no string table.
             strTab.clear();
             return Common::Result::Ok();
        }

        if (header.e_shstrndx >= sections.size()) {
             return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Invalid Section Header String Table Index");
        }

        const auto& shstrtab_hdr = sections[header.e_shstrndx];

        // Safety check on size (e.g., 100MB limit)
        if (shstrtab_hdr.sh_size > 100 * 1024 * 1024) {
             return Common::Result::Fail(Common::StatusCode::InvalidFormat, "String table too large");
        }

        if (shstrtab_hdr.sh_size == 0) {
            strTab.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(shstrtab_hdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to SH String Table");
        }

        strTab.resize(shstrtab_hdr.sh_size);
        if (!reader.Read(strTab.data(), shstrtab_hdr.sh_size)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read SH String Table");
        }

        return Common::Result::Ok();
    }

    std::string SectionParser::GetSectionName(const std::vector<char>& strTab, uint32_t offset) {
        if (strTab.empty() || offset >= strTab.size()) return "";

        size_t len = 0;
        for (size_t i = offset; i < strTab.size(); ++i) {
            if (strTab[i] == '\0') break;
            len++;
        }
        return std::string(&strTab[offset], len);
    }

}
