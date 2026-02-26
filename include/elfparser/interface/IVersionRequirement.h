#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "elfparser/interface/INode.h"

namespace ElfParser::Interface {

    struct VersionDependency {
        std::string name;
        uint32_t hash;
        uint16_t flags;
        uint16_t other;
    };

    /**
     * @brief Interface for Version Requirements.
     */
    class IVersionRequirement : public INode {
    public:
        virtual ~IVersionRequirement() = default;

        virtual uint16_t GetVersion() const = 0;
        virtual void SetVersion(uint16_t version) = 0;

        virtual const std::string& GetFileName() const = 0;
        virtual void SetFileName(const std::string& fileName) = 0;

        virtual uint16_t GetCount() const = 0;

        virtual const std::vector<VersionDependency>& GetDependencies() const = 0;
        virtual void SetDependencies(const std::vector<VersionDependency>& dependencies) = 0;
    };

}
