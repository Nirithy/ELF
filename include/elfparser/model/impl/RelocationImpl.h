#pragma once

#include "elfparser/interface/IRelocation.h"
#include "elfparser/interface/IVisitor.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Model::Impl {

    class RelocationImpl : public Interface::IRelocation {
    public:
        explicit RelocationImpl(const Elf64_Rela& rela)
            : m_rela(rela) {}

        uint64_t GetOffset() const override { return m_rela.r_offset; }
        void SetOffset(uint64_t offset) override { m_rela.r_offset = offset; }

        uint64_t GetInfo() const { return m_rela.r_info; }
        void SetInfo(uint64_t info) { m_rela.r_info = info; }

        int64_t GetAddend() const override { return m_rela.r_addend; }
        void SetAddend(int64_t addend) override { m_rela.r_addend = addend; }

        bool IsRela() const override { return true; }

        uint32_t GetType() const override {
            return static_cast<uint32_t>(m_rela.r_info & 0xFFFFFFFFL);
        }
        void SetType(uint32_t type) override {
            m_rela.r_info = (m_rela.r_info & 0xFFFFFFFF00000000L) | (type & 0xFFFFFFFFL);
        }

        uint32_t GetSymbolIndex() const override {
            return static_cast<uint32_t>(m_rela.r_info >> 32);
        }
        void SetSymbolIndex(uint32_t index) override {
            m_rela.r_info = (static_cast<uint64_t>(index) << 32) | (m_rela.r_info & 0xFFFFFFFFL);
        }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

        const Elf64_Rela& GetRaw() const { return m_rela; }

    private:
        Elf64_Rela m_rela;
    };

}
