#include "elfparser/builder/components/sections/symbols/SymbolTableBuilder.h"
#include "elfparser/utils/ElfSwap.h"
#include <cstring>

namespace ElfParser::Builder::Components {

    SymbolTableBuilder::SymbolTableBuilder(StringTableBuilder& strtab, const std::string& name)
        : m_strtab(strtab) {
        SetName(name);
        SetType(Model::ElfSectionType::Symtab);
        SetEntSize(sizeof(Model::Elf64_Sym));
        // Link will be set later, usually to strtab's index.
        SetInfo(0); // One greater than the symbol table index of the last local symbol (STB_LOCAL). Updated as we go.

        // The first entry in the symbol table must be all zeros (STN_UNDEF).
        Model::Elf64_Sym nullSym{};
        std::memset(&nullSym, 0, sizeof(nullSym));
        m_symbols.push_back(nullSym);
    }

    uint32_t SymbolTableBuilder::AddSymbol(Model::Elf64_Sym symbol, const std::string& name) {
        if (!name.empty()) {
            symbol.st_name = m_strtab.AddString(name);
        }

        // Update ST_INFO if needed?
        // We trust the user to set st_info correctly (binding, type).
        // However, we should probably update sh_info (count of local symbols).
        // According to ELF spec, sh_info contains the index of the first non-local symbol.
        // Or 1 + index of last local symbol.
        // Basically, all LOCAL symbols must come first.
        // Since we are just appending, we assume the user adds locals first.
        // If the user adds a global, we should stop counting locals?
        // For now, let's keep it simple and just append.
        // A more advanced builder would sort symbols.

        m_symbols.push_back(symbol);

        // Update sh_info if this is a local symbol
        // (This logic assumes local symbols are added first)
        unsigned char binding = symbol.st_info >> 4;
        if (binding == static_cast<unsigned char>(Model::ElfSymbolBinding::Local)) {
             SetInfo(static_cast<uint32_t>(m_symbols.size()));
        }

        return static_cast<uint32_t>(m_symbols.size() - 1);
    }

    Common::Result SymbolTableBuilder::Write(IO::BinaryWriter& writer) {
        for (auto sym : m_symbols) {
            // Check if we need to swap endianness
            if (writer.ShouldSwap()) {
                Utils::Swap(sym);
            }
            // Write the symbol
            auto result = writer.Write(&sym, sizeof(sym));
            if (!result.IsOk()) {
                return result;
            }
        }
        return Common::Result::Ok();
    }

    uint64_t SymbolTableBuilder::GetSize() const {
        return m_symbols.size() * sizeof(Model::Elf64_Sym);
    }

}
