#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/components/sections/strings/StringTableBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    struct VersionDefEntry {
        uint16_t flags;
        uint16_t ndx;
        uint32_t cnt;
        uint32_t hash;
        std::vector<std::string> auxNames; // First is the version name, subsequent are parents
    };

    class VersionDefinitionBuilder : public SectionBuilder {
    public:
        explicit VersionDefinitionBuilder(StringTableBuilder& dynstr, const std::string& name = ".gnu.version_d");

        // Add a version definition
        void AddDefinition(uint16_t flags, uint16_t ndx, uint32_t hash, const std::vector<std::string>& names);

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        StringTableBuilder& m_dynstr;
        std::vector<VersionDefEntry> m_definitions;
    };

}
