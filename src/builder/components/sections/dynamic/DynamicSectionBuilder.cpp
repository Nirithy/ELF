#include "elfparser/builder/components/sections/dynamic/DynamicSectionBuilder.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Builder::Components {

    DynamicSectionBuilder::DynamicSectionBuilder(StringTableBuilder& dynstr, const std::string& name)
        : m_dynstr(dynstr) {
        SetName(name);
        SetType(Model::ElfSectionType::Dynamic);
        SetEntSize(sizeof(Model::Elf64_Dyn));
        // Link to string table needs to be set later
    }

    void DynamicSectionBuilder::AddEntry(Model::Elf64_Dyn entry, const std::string& stringValue) {
        if (!stringValue.empty()) {
            // Add string to .dynstr and update d_val
            entry.d_un.d_val = m_dynstr.AddString(stringValue);
        }

        m_entries.push_back(entry);
    }

    Common::Result DynamicSectionBuilder::Write(IO::BinaryWriter& writer) {
        for (auto entry : m_entries) {
            if (writer.ShouldSwap()) {
                Utils::Swap(entry);
            }
            auto result = writer.Write(&entry, sizeof(entry));
            if (!result.IsOk()) {
                return result;
            }
        }
        return Common::Result::Ok();
    }

    uint64_t DynamicSectionBuilder::GetSize() const {
        return m_entries.size() * sizeof(Model::Elf64_Dyn);
    }

}
