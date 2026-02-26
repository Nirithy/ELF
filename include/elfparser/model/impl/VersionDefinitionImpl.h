#pragma once

#include "elfparser/interface/IVersionDefinition.h"
#include "elfparser/interface/IVisitor.h"
#include <vector>
#include <string>

namespace ElfParser::Model::Impl {

    class VersionDefinitionImpl : public Interface::IVersionDefinition {
    public:
        VersionDefinitionImpl() = default;

        uint16_t GetVersion() const override { return m_version; }
        void SetVersion(uint16_t version) override { m_version = version; }

        uint16_t GetFlags() const override { return m_flags; }
        void SetFlags(uint16_t flags) override { m_flags = flags; }

        uint16_t GetIndex() const override { return m_index; }
        void SetIndex(uint16_t index) override { m_index = index; }

        uint16_t GetAuxiliaryCount() const override { return static_cast<uint16_t>(m_auxNames.size()); }
        void SetAuxiliaryCount(uint16_t count) override {
            // Usually managed by vector size, but kept for interface compliance if needed manually
            // Here we ignore it or resize vector? Let's rely on vector size.
        }

        uint32_t GetHash() const override { return m_hash; }
        void SetHash(uint32_t hash) override { m_hash = hash; }

        const std::vector<std::string>& GetAuxiliaryNames() const override { return m_auxNames; }
        void SetAuxiliaryNames(const std::vector<std::string>& names) override { m_auxNames = names; }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

    private:
        uint16_t m_version = 1;
        uint16_t m_flags = 0;
        uint16_t m_index = 0;
        uint32_t m_hash = 0;
        std::vector<std::string> m_auxNames;
    };

}
