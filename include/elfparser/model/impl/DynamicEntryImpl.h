#pragma once

#include "elfparser/interface/IDynamicEntry.h"
#include "elfparser/interface/IVisitor.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Model::Impl {

    class DynamicEntryImpl : public Interface::IDynamicEntry {
    public:
        explicit DynamicEntryImpl(const Elf64_Dyn& dyn)
            : m_dyn(dyn) {}

        Model::ElfDynamicTag GetTag() const override {
            return static_cast<Model::ElfDynamicTag>(m_dyn.d_tag);
        }
        void SetTag(Model::ElfDynamicTag tag) override {
            m_dyn.d_tag = static_cast<uint64_t>(tag);
        }

        uint64_t GetValue() const override { return m_dyn.d_un.d_val; }
        void SetValue(uint64_t value) override { m_dyn.d_un.d_val = value; }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

        const Elf64_Dyn& GetRaw() const { return m_dyn; }

    private:
        Elf64_Dyn m_dyn;
    };

}
