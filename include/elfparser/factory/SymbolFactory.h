#pragma once

#include <memory>
#include <string>
#include "elfparser/interface/ISymbol.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Factory {

    class SymbolFactory {
    public:
        /**
         * @brief Creates a new Symbol instance.
         * @param sym The raw symbol structure.
         * @param name The name of the symbol.
         * @return A unique pointer to the created symbol.
         */
        static std::unique_ptr<Interface::ISymbol> CreateSymbol(const Model::Elf64_Sym& sym, const std::string& name);
    };

}
