#include "elfparser/parser/components/sections/symbols/SymbolTableParser.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser::Components {

    Common::Result SymbolTableParser::Parse(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, const Model::Elf64_Shdr& section, std::vector<Model::Elf64_Sym>& symbols) {
        // Validate section type
        // Note: SHT_SYMTAB = 2, SHT_DYNSYM = 11
        // We cast to uint32_t for comparison
        if (section.sh_type != static_cast<uint32_t>(Model::ElfSectionType::Symtab) &&
            section.sh_type != static_cast<uint32_t>(Model::ElfSectionType::Dynsym)) {
            // Not a symbol table, strictly speaking this parser might be called on wrong section
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "Section is not a symbol table");
        }

        if (section.sh_size == 0) {
            symbols.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(section.sh_offset)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Symbol Table");
        }

        // Determine if we are reading 32-bit or 64-bit entries
        // EI_CLASS is at index 4
        auto elfClass = static_cast<Model::ElfClass>(header.e_ident[4]);

        size_t entryCount = 0;
        if (section.sh_entsize > 0) {
            entryCount = section.sh_size / section.sh_entsize;
        } else {
            // Fallback if entsize is 0 (shouldn't happen for valid ELF)
             if (elfClass == Model::ElfClass::Elf64) {
                 entryCount = section.sh_size / sizeof(Model::Elf64_Sym);
             } else {
                 entryCount = section.sh_size / sizeof(Model::Elf32_Sym);
             }
        }

        symbols.clear();
        symbols.reserve(entryCount);

        if (elfClass == Model::ElfClass::Elf64) {
            for (size_t i = 0; i < entryCount; ++i) {
                Model::Elf64_Sym sym;
                if (!reader.Read(sym)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Symbol Entry " + std::to_string(i));
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(sym);
                }
                symbols.push_back(sym);
            }
        } else if (elfClass == Model::ElfClass::Elf32) {
             for (size_t i = 0; i < entryCount; ++i) {
                Model::Elf32_Sym sym32;
                if (!reader.Read(sym32)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Symbol Entry " + std::to_string(i));
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(sym32);
                }

                // Convert to 64-bit
                Model::Elf64_Sym sym64;
                sym64.st_name = sym32.st_name;
                sym64.st_info = sym32.st_info;
                sym64.st_other = sym32.st_other;
                sym64.st_shndx = sym32.st_shndx;
                sym64.st_value = sym32.st_value;
                sym64.st_size = sym32.st_size;

                symbols.push_back(sym64);
            }
        } else {
            return Common::Result::Fail(Common::StatusCode::NotImplemented, "Unknown ELF Class");
        }

        return Common::Result::Ok();
    }

}
