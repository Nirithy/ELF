#pragma once

#include <cstdint>
#include "elfparser/interface/INode.h"
#include "elfparser/model/enums/ElfSegmentType.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for ELF Segments.
     * Represents a Program Header entry describing a memory segment.
     */
    class ISegment : public INode {
    public:
        virtual ~ISegment() = default;

        // Type
        virtual Model::ElfSegmentType GetType() const = 0;
        virtual void SetType(Model::ElfSegmentType type) = 0;

        // Flags
        virtual uint32_t GetFlags() const = 0;
        virtual void SetFlags(uint32_t flags) = 0;

        // Offset
        virtual uint64_t GetOffset() const = 0;
        virtual void SetOffset(uint64_t offset) = 0;

        // Virtual Address
        virtual uint64_t GetVAddr() const = 0;
        virtual void SetVAddr(uint64_t vaddr) = 0;

        // Physical Address
        virtual uint64_t GetPAddr() const = 0;
        virtual void SetPAddr(uint64_t paddr) = 0;

        // File Size
        virtual uint64_t GetFileSize() const = 0;
        virtual void SetFileSize(uint64_t fileSize) = 0;

        // Memory Size
        virtual uint64_t GetMemSize() const = 0;
        virtual void SetMemSize(uint64_t memSize) = 0;

        // Alignment
        virtual uint64_t GetAlign() const = 0;
        virtual void SetAlign(uint64_t align) = 0;
    };

}
