#pragma once

#include <string>
#include <cstdint>
#include "elfparser/interface/INode.h"
#include "elfparser/model/enums/ElfSectionType.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for ELF Sections.
     * Provides access to section properties and content management.
     */
    class ISection : public INode {
    public:
        virtual ~ISection() = default;

        // Name
        virtual const std::string& GetName() const = 0;
        virtual void SetName(const std::string& name) = 0;

        // Type
        virtual Model::ElfSectionType GetType() const = 0;
        virtual void SetType(Model::ElfSectionType type) = 0;

        // Flags
        virtual uint64_t GetFlags() const = 0;
        virtual void SetFlags(uint64_t flags) = 0;

        // Address
        virtual uint64_t GetAddr() const = 0;
        virtual void SetAddr(uint64_t addr) = 0;

        // Offset
        virtual uint64_t GetOffset() const = 0;
        virtual void SetOffset(uint64_t offset) = 0;

        // Size
        virtual uint64_t GetSize() const = 0;
        virtual void SetSize(uint64_t size) = 0;

        // Link
        virtual uint32_t GetLink() const = 0;
        virtual void SetLink(uint32_t link) = 0;

        // Info
        virtual uint32_t GetInfo() const = 0;
        virtual void SetInfo(uint32_t info) = 0;

        // Address Alignment
        virtual uint64_t GetAddrAlign() const = 0;
        virtual void SetAddrAlign(uint64_t align) = 0;

        // Entry Size
        virtual uint64_t GetEntSize() const = 0;
        virtual void SetEntSize(uint64_t entsize) = 0;

        // Visitor Accept (Already in INode, but good to be explicit or override if needed)
        // virtual void Accept(IVisitor& visitor) override = 0;
    };

}
