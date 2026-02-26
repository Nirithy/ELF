#pragma once

#include "elfparser/interface/IVersionRequirement.h"
#include "elfparser/interface/IVisitor.h"

namespace ElfParser::Model::Impl {

    class VersionRequirementImpl : public Interface::IVersionRequirement {
    public:
        VersionRequirementImpl() = default;

        uint16_t GetVersion() const override { return m_version; }
        void SetVersion(uint16_t version) override { m_version = version; }

        const std::string& GetFileName() const override { return m_fileName; }
        void SetFileName(const std::string& fileName) override { m_fileName = fileName; }

        uint16_t GetCount() const override { return static_cast<uint16_t>(m_dependencies.size()); }

        const std::vector<Interface::VersionDependency>& GetDependencies() const override { return m_dependencies; }
        void SetDependencies(const std::vector<Interface::VersionDependency>& dependencies) override { m_dependencies = dependencies; }

        void Accept(Interface::IVisitor& visitor) override {
            visitor.Visit(*this);
        }

    private:
        uint16_t m_version = 1;
        std::string m_fileName;
        std::vector<Interface::VersionDependency> m_dependencies;
    };

}
