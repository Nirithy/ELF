#pragma once

#include "elfparser/interface/ISymbol.h"
#include "elfparser/interface/IVisitor.h"
#include "elfparser/model/ElfStructures.h"
#include <string>

namespace ElfParser::Model::Impl {

    class SymbolImpl : public Interface::ISymbol {
    public:
        SymbolImpl(const Elf64_Sym& sym, const std::string& name)
            : m_sym(sym), m_name(name) {}

        const std::string& GetName() const override { return m_name; }
        void SetName(const std::string& name) override { m_name = name; }

        uint64_t GetValue() const override { return m_sym.st_value; }
        void SetValue(uint64_t value) override { m_sym.st_value = value; }

        uint64_t GetSize() const override { return m_sym.st_size; }
        void SetSize(uint64_t size) override { m_sym.st_size = size; }

        ElfSymbolBinding GetBinding() const override {
            return static_cast<ElfSymbolBinding>(m_sym.st_info >> 4);
        }
        void SetBinding(ElfSymbolBinding binding) override {
            m_sym.st_info = (static_cast<unsigned char>(binding) << 4) | (m_sym.st_info & 0x0F);
        }

        ElfSymbolType GetType() const override {
            return static_cast<ElfSymbolType>(m_sym.st_info & 0x0F);
        }
        void SetType(ElfSymbolType type) override {
            m_sym.st_info = (m_sym.st_info & 0xF0) | static_cast<unsigned char>(type);
        }

        ElfSymbolVisibility GetVisibility() const override {
            return static_cast<ElfSymbolVisibility>(m_sym.st_other & 0x03);
        }
        void SetVisibility(ElfSymbolVisibility visibility) override {
            m_sym.st_other = (m_sym.st_other & 0xFC) | static_cast<unsigned char>(visibility);
        }

        uint16_t GetSectionIndex() const override { return m_sym.st_shndx; }
        void SetSectionIndex(uint16_t index) override { m_sym.st_shndx = index; }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

        // Helper to get raw struct
        const Elf64_Sym& GetRaw() const { return m_sym; }

    private:
        Elf64_Sym m_sym;
        std::string m_name;
    };

}
