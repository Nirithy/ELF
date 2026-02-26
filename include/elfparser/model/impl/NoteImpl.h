#pragma once

#include "elfparser/interface/INote.h"
#include "elfparser/interface/IVisitor.h"

namespace ElfParser::Model::Impl {

    class NoteImpl : public Interface::INote {
    public:
        NoteImpl(uint32_t type, const std::string& name, const std::vector<unsigned char>& desc)
            : m_type(type), m_name(name), m_desc(desc) {}

        uint32_t GetType() const override { return m_type; }
        void SetType(uint32_t type) override { m_type = type; }

        const std::string& GetName() const override { return m_name; }
        void SetName(const std::string& name) override { m_name = name; }

        const std::vector<unsigned char>& GetDescriptor() const override { return m_desc; }
        void SetDescriptor(const std::vector<unsigned char>& desc) override { m_desc = desc; }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

    private:
        uint32_t m_type;
        std::string m_name;
        std::vector<unsigned char> m_desc;
    };

}
