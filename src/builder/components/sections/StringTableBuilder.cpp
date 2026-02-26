#include "elfparser/builder/components/sections/StringTableBuilder.h"

namespace ElfParser::Builder::Components {

    StringTableBuilder::StringTableBuilder(const std::string& name) {
        SetName(name);
        SetType(Model::ElfSectionType::Strtab);
        SetAddralign(1);

        // String tables always start with a null byte
        m_data.push_back('\0');
        m_stringMap[""] = 0;
    }

    uint32_t StringTableBuilder::AddString(const std::string& str) {
        if (str.empty()) {
            return 0;
        }

        auto it = m_stringMap.find(str);
        if (it != m_stringMap.end()) {
            return it->second;
        }

        uint32_t offset = static_cast<uint32_t>(m_data.size());

        // Append string and null terminator
        m_data.insert(m_data.end(), str.begin(), str.end());
        m_data.push_back('\0');

        m_stringMap[str] = offset;
        return offset;
    }

    Common::Result StringTableBuilder::Write(IO::BinaryWriter& writer) {
        return writer.Write(m_data.data(), m_data.size());
    }

    uint64_t StringTableBuilder::GetSize() const {
        return m_data.size();
    }

}
