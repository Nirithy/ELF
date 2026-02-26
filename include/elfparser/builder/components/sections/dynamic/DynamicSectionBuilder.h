#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/components/sections/StringTableBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    class DynamicSectionBuilder : public SectionBuilder {
    public:
        // Constructor takes a reference to the dynamic string table (.dynstr).
        explicit DynamicSectionBuilder(StringTableBuilder& dynstr, const std::string& name = ".dynamic");

        // Adds a dynamic entry.
        // If stringValue is provided (e.g. for DT_NEEDED), it is added to the string table
        // and the entry's d_val is updated with the offset.
        void AddEntry(Model::Elf64_Dyn entry, const std::string& stringValue = "");

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        StringTableBuilder& m_dynstr;
        std::vector<Model::Elf64_Dyn> m_entries;
    };

}
