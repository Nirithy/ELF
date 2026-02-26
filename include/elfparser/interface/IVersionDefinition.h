#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "elfparser/interface/INode.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for Version Definitions.
     */
    class IVersionDefinition : public INode {
    public:
        virtual ~IVersionDefinition() = default;

        virtual uint16_t GetVersion() const = 0;
        virtual void SetVersion(uint16_t version) = 0;

        virtual uint16_t GetFlags() const = 0;
        virtual void SetFlags(uint16_t flags) = 0;

        virtual uint16_t GetIndex() const = 0;
        virtual void SetIndex(uint16_t index) = 0;

        virtual uint16_t GetAuxiliaryCount() const = 0;
        virtual void SetAuxiliaryCount(uint16_t count) = 0;

        virtual uint32_t GetHash() const = 0;
        virtual void SetHash(uint32_t hash) = 0;

        virtual const std::vector<std::string>& GetAuxiliaryNames() const = 0;
        virtual void SetAuxiliaryNames(const std::vector<std::string>& names) = 0;
    };

}
