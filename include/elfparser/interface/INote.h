#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "elfparser/interface/INode.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for ELF Notes.
     */
    class INote : public INode {
    public:
        virtual ~INote() = default;

        virtual uint32_t GetType() const = 0;
        virtual void SetType(uint32_t type) = 0;

        virtual const std::string& GetName() const = 0;
        virtual void SetName(const std::string& name) = 0;

        virtual const std::vector<unsigned char>& GetDescriptor() const = 0;
        virtual void SetDescriptor(const std::vector<unsigned char>& desc) = 0;
    };

}
