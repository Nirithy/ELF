#include "elfparser/parser/components/sections/DynamicSectionParser.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Parser::Components {

    Common::Result DynamicSectionParser::Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Dyn>& dynamics) {
        if (section.sh_type != static_cast<uint32_t>(Model::ElfSectionType::Dynamic)) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Section is not a dynamic section");
        }

        if (section.sh_size == 0) {
            dynamics.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(section.sh_offset)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Dynamic Section");
        }

        // Determine 32/64 bit
        auto elfClass = static_cast<Model::ElfClass>(header.e_ident[4]);

        size_t entryCount = 0;
        if (section.sh_entsize > 0) {
            entryCount = section.sh_size / section.sh_entsize;
        } else {
             if (elfClass == Model::ElfClass::Elf64) {
                 entryCount = section.sh_size / sizeof(Model::Elf64_Dyn);
             } else {
                 entryCount = section.sh_size / sizeof(Model::Elf32_Dyn);
             }
        }

        dynamics.clear();
        dynamics.reserve(entryCount);

        if (elfClass == Model::ElfClass::Elf64) {
            for (size_t i = 0; i < entryCount; ++i) {
                Model::Elf64_Dyn dyn;
                if (!reader.Read(dyn)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Dynamic Entry " + std::to_string(i));
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(dyn);
                }
                dynamics.push_back(dyn);
            }
        } else if (elfClass == Model::ElfClass::Elf32) {
            for (size_t i = 0; i < entryCount; ++i) {
                Model::Elf32_Dyn dyn32;
                if (!reader.Read(dyn32)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Dynamic Entry " + std::to_string(i));
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(dyn32);
                }

                // Convert
                Model::Elf64_Dyn dyn64;
                dyn64.d_tag = dyn32.d_tag;
                dyn64.d_un.d_val = dyn32.d_un.d_val;

                dynamics.push_back(dyn64);
            }
        } else {
            return Common::Result::Fail(Common::StatusCode::NotImplemented, "Unknown ELF Class");
        }

        return Common::Result::Ok();
    }
}
