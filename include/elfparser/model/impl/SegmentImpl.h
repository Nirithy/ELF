#pragma once

#include "elfparser/interface/ISegment.h"
#include "elfparser/interface/IVisitor.h"
#include "elfparser/model/structs/ElfPhdr.h"

namespace ElfParser::Model {

    /**
     * @brief Concrete implementation of ISegment.
     */
    class SegmentImpl : public Interface::ISegment {
    public:
        explicit SegmentImpl(ElfSegmentType type = ElfSegmentType::Null) {
            m_header.p_type = static_cast<uint32_t>(type);
        }

        ~SegmentImpl() override = default;

        ElfSegmentType GetType() const override { return static_cast<ElfSegmentType>(m_header.p_type); }
        void SetType(ElfSegmentType type) override { m_header.p_type = static_cast<uint32_t>(type); }

        uint32_t GetFlags() const override { return m_header.p_flags; }
        void SetFlags(uint32_t flags) override { m_header.p_flags = flags; }

        uint64_t GetOffset() const override { return m_header.p_offset; }
        void SetOffset(uint64_t offset) override { m_header.p_offset = offset; }

        uint64_t GetVAddr() const override { return m_header.p_vaddr; }
        void SetVAddr(uint64_t vaddr) override { m_header.p_vaddr = vaddr; }

        uint64_t GetPAddr() const override { return m_header.p_paddr; }
        void SetPAddr(uint64_t paddr) override { m_header.p_paddr = paddr; }

        uint64_t GetFileSize() const override { return m_header.p_filesz; }
        void SetFileSize(uint64_t fileSize) override { m_header.p_filesz = fileSize; }

        uint64_t GetMemSize() const override { return m_header.p_memsz; }
        void SetMemSize(uint64_t memSize) override { m_header.p_memsz = memSize; }

        uint64_t GetAlign() const override { return m_header.p_align; }
        void SetAlign(uint64_t align) override { m_header.p_align = align; }

        void Accept(Interface::IVisitor& visitor) override { visitor.Visit(*this); }

    private:
        Elf64_Phdr m_header{};
    };

}
