#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/components/sections/strings/StringTableBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    struct VersionNeedAuxEntry {
        uint32_t hash;
        uint16_t flags;
        uint16_t other;
        std::string name;
    };

    struct VersionNeedEntry {
        std::string filename;
        std::vector<VersionNeedAuxEntry> auxEntries;
    };

    class VersionRequirementBuilder : public SectionBuilder {
    public:
        explicit VersionRequirementBuilder(StringTableBuilder& dynstr, const std::string& name = ".gnu.version_r");

        // Add a requirement
        void AddRequirement(const std::string& filename, const std::vector<VersionNeedAuxEntry>& auxEntries);

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        StringTableBuilder& m_dynstr;
        std::vector<VersionNeedEntry> m_requirements;
    };

}
