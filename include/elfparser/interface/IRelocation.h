#pragma once

#include <cstdint>
#include "elfparser/interface/INode.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for ELF Relocations (REL and RELA).
     */
    class IRelocation : public INode {
    public:
        virtual ~IRelocation() = default;

        // The location at which to apply the relocation action.
        virtual uint64_t GetOffset() const = 0;
        virtual void SetOffset(uint64_t offset) = 0;

        // The symbol table index with respect to which the relocation must be made.
        virtual uint32_t GetSymbolIndex() const = 0;
        virtual void SetSymbolIndex(uint32_t index) = 0;

        // The type of relocation to apply.
        virtual uint32_t GetType() const = 0;
        virtual void SetType(uint32_t type) = 0;

        // A constant addend used to compute the value to be stored into the relocatable field.
        // For REL entries, this should return 0 or the implicit addend.
        virtual int64_t GetAddend() const = 0;
        virtual void SetAddend(int64_t addend) = 0;

        // Indicates if this is a RELA entry (has explicit addend).
        virtual bool IsRela() const = 0;
    };

}
