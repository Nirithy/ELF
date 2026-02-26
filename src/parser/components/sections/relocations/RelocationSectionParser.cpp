#include "elfparser/parser/components/sections/relocations/RelocationSectionParser.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Parser::Components {

    Common::Result RelocationSectionParser::Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Rela>& relocations) {
        bool isRela = (section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Rela));
        bool isRel = (section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Rel));

        if (!isRela && !isRel) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Section is not a relocation section");
        }

        if (section.sh_size == 0) {
            relocations.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(section.sh_offset)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Relocation Section");
        }

        auto elfClass = static_cast<Model::ElfClass>(header.e_ident[4]);

        size_t entryCount = 0;
        if (section.sh_entsize > 0) {
            entryCount = section.sh_size / section.sh_entsize;
        } else {
             // Fallback
             if (elfClass == Model::ElfClass::Elf64) {
                 entryCount = section.sh_size / (isRela ? sizeof(Model::Elf64_Rela) : sizeof(Model::Elf64_Rel));
             } else {
                 entryCount = section.sh_size / (isRela ? sizeof(Model::Elf32_Rela) : sizeof(Model::Elf32_Rel));
             }
        }

        relocations.clear();
        relocations.reserve(entryCount);

        if (elfClass == Model::ElfClass::Elf64) {
            if (isRela) {
                for (size_t i = 0; i < entryCount; ++i) {
                    Model::Elf64_Rela rela;
                    if (!reader.Read(rela)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read RELA");
                    if (reader.ShouldSwap()) Utils::Swap(rela);
                    relocations.push_back(rela);
                }
            } else {
                for (size_t i = 0; i < entryCount; ++i) {
                    Model::Elf64_Rel rel;
                    if (!reader.Read(rel)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read REL");
                    if (reader.ShouldSwap()) Utils::Swap(rel);

                    Model::Elf64_Rela rela;
                    rela.r_offset = rel.r_offset;
                    rela.r_info = rel.r_info;
                    rela.r_addend = 0; // REL has implicit addend
                    relocations.push_back(rela);
                }
            }
        } else if (elfClass == Model::ElfClass::Elf32) {
             if (isRela) {
                for (size_t i = 0; i < entryCount; ++i) {
                    Model::Elf32_Rela rela32;
                    if (!reader.Read(rela32)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read RELA");
                    if (reader.ShouldSwap()) Utils::Swap(rela32);

                    Model::Elf64_Rela rela64;
                    rela64.r_offset = rela32.r_offset;

                    // Convert r_info
                    uint32_t sym = (rela32.r_info >> 8);
                    uint32_t type = (unsigned char)(rela32.r_info);
                    rela64.r_info = (((uint64_t)sym) << 32) | (type & 0xffffffffL);

                    rela64.r_addend = rela32.r_addend;
                    relocations.push_back(rela64);
                }
            } else {
                for (size_t i = 0; i < entryCount; ++i) {
                    Model::Elf32_Rel rel32;
                    if (!reader.Read(rel32)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read REL");
                    if (reader.ShouldSwap()) Utils::Swap(rel32);

                    Model::Elf64_Rela rela64;
                    rela64.r_offset = rel32.r_offset;

                    // Convert r_info
                    uint32_t sym = (rel32.r_info >> 8);
                    uint32_t type = (unsigned char)(rel32.r_info);
                    rela64.r_info = (((uint64_t)sym) << 32) | (type & 0xffffffffL);

                    rela64.r_addend = 0;
                    relocations.push_back(rela64);
                }
            }
        } else {
            return Common::Result::Fail(Common::StatusCode::NotImplemented, "Unknown ELF Class");
        }

        return Common::Result::Ok();
    }
}
