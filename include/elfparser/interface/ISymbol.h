#pragma once

#include <string>
#include <cstdint>
#include "elfparser/interface/INode.h"
#include "elfparser/model/enums/ElfSymbolBinding.h"
#include "elfparser/model/enums/ElfSymbolType.h"
#include "elfparser/model/enums/ElfSymbolVisibility.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for ELF Symbols.
     */
    class ISymbol : public INode {
    public:
        virtual ~ISymbol() = default;

        virtual const std::string& GetName() const = 0;
        virtual void SetName(const std::string& name) = 0;

        virtual uint64_t GetValue() const = 0;
        virtual void SetValue(uint64_t value) = 0;

        virtual uint64_t GetSize() const = 0;
        virtual void SetSize(uint64_t size) = 0;

        virtual Model::ElfSymbolBinding GetBinding() const = 0;
        virtual void SetBinding(Model::ElfSymbolBinding binding) = 0;

        virtual Model::ElfSymbolType GetType() const = 0;
        virtual void SetType(Model::ElfSymbolType type) = 0;

        virtual Model::ElfSymbolVisibility GetVisibility() const = 0;
        virtual void SetVisibility(Model::ElfSymbolVisibility visibility) = 0;

        virtual uint16_t GetSectionIndex() const = 0;
        virtual void SetSectionIndex(uint16_t index) = 0;
    };

}
