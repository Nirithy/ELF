#pragma once

#include "elfparser/builder/components/sections/SectionBuilder.h"
#include <map>
#include <vector>
#include <string>

namespace ElfParser::Builder::Components {

    class StringTableBuilder : public SectionBuilder {
    public:
        StringTableBuilder(const std::string& name = ".strtab");

        // Adds a string and returns its offset in the table.
        // If the string already exists, returns the existing offset.
        uint32_t AddString(const std::string& str);

        // Implements SectionBuilder
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        std::vector<char> m_data;
        std::map<std::string, uint32_t> m_stringMap;
    };

}
