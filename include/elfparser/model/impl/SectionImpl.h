#pragma once

#include <string>
#include "elfparser/interface/ISection.h"
#include "elfparser/interface/IVisitor.h"
#include "elfparser/model/structs/ElfShdr.h"

namespace ElfParser::Model {

    /**
     * @brief Concrete implementation of ISection.
     */
    class SectionImpl : public Interface::ISection {
    public:
        explicit SectionImpl(const std::string& name = "", ElfSectionType type = ElfSectionType::Null)
            : m_name(name) {
            m_header.sh_type = static_cast<uint32_t>(type);
        }

        ~SectionImpl() override = default;

        const std::string& GetName() const override { return m_name; }
        void SetName(const std::string& name) override { m_name = name; }

        ElfSectionType GetType() const override { return static_cast<ElfSectionType>(m_header.sh_type); }
        void SetType(ElfSectionType type) override { m_header.sh_type = static_cast<uint32_t>(type); }

        uint64_t GetFlags() const override { return m_header.sh_flags; }
        void SetFlags(uint64_t flags) override { m_header.sh_flags = flags; }

        uint64_t GetAddr() const override { return m_header.sh_addr; }
        void SetAddr(uint64_t addr) override { m_header.sh_addr = addr; }

        uint64_t GetOffset() const override { return m_header.sh_offset; }
        void SetOffset(uint64_t offset) override { m_header.sh_offset = offset; }

        uint64_t GetSize() const override { return m_header.sh_size; }
        void SetSize(uint64_t size) override { m_header.sh_size = size; }

        uint32_t GetLink() const override { return m_header.sh_link; }
        void SetLink(uint32_t link) override { m_header.sh_link = link; }

        uint32_t GetInfo() const override { return m_header.sh_info; }
        void SetInfo(uint32_t info) override { m_header.sh_info = info; }

        uint64_t GetAddrAlign() const override { return m_header.sh_addralign; }
        void SetAddrAlign(uint64_t align) override { m_header.sh_addralign = align; }

        uint64_t GetEntSize() const override { return m_header.sh_entsize; }
        void SetEntSize(uint64_t entsize) override { m_header.sh_entsize = entsize; }

        void Accept(Interface::IVisitor& visitor) override { visitor.Visit(*this); }

    private:
        std::string m_name;
        Elf64_Shdr m_header{};
    };

}
