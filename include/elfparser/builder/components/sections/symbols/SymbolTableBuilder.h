#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/components/sections/StringTableBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    class SymbolTableBuilder : public SectionBuilder {
    public:
        // Constructor takes a reference to the string table used for symbol names.
        // It automatically adds the initial NULL symbol required by ELF specification.
        explicit SymbolTableBuilder(StringTableBuilder& strtab, const std::string& name = ".symtab");

        // Adds a symbol to the table.
        // If name is provided, it is added to the string table and st_name is updated.
        // Returns the index of the added symbol.
        uint32_t AddSymbol(Model::Elf64_Sym symbol, const std::string& name = "");

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        StringTableBuilder& m_strtab;
        std::vector<Model::Elf64_Sym> m_symbols;
    };

}
