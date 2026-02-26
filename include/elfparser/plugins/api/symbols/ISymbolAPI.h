#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class ISymbol;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Symbols.
     */
    class ISymbolAPI {
    public:
        virtual ~ISymbolAPI() = default;

        /**
         * @brief Get a symbol by name.
         */
        virtual Interface::ISymbol* GetSymbol(const std::string& name) = 0;

        /**
         * @brief Get all symbols.
         */
        virtual std::vector<Interface::ISymbol*> GetAllSymbols() = 0;

        /**
         * @brief Add a new symbol.
         */
        virtual Interface::ISymbol* AddSymbol(const std::string& name) = 0;

        /**
         * @brief Remove a symbol.
         */
        virtual Common::Result RemoveSymbol(const std::string& name) = 0;
    };

}
