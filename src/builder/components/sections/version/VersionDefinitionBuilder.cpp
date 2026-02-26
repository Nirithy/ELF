#include "elfparser/builder/components/sections/version/VersionDefinitionBuilder.h"
#include "elfparser/io/BinaryWriter.h"

namespace ElfParser::Builder::Components {

    VersionDefinitionBuilder::VersionDefinitionBuilder(StringTableBuilder& dynstr, const std::string& name)
        : m_dynstr(dynstr) {
        SetName(name);
        SetType(Model::ElfSectionType::GnuVerDef);
        SetEntSize(0);
        SetAddralign(4);
        SetInfo(0);
    }

    void VersionDefinitionBuilder::AddDefinition(uint16_t flags, uint16_t ndx, uint32_t hash, const std::vector<std::string>& names) {
        m_definitions.push_back({flags, ndx, static_cast<uint32_t>(names.size()), hash, names});
        // Update Info (sh_info) which is the number of definitions
        SetInfo(static_cast<uint32_t>(m_definitions.size()));

        // Add strings to dynstr
        for(const auto& name : names) {
            m_dynstr.AddString(name);
        }
    }

    Common::Result VersionDefinitionBuilder::Write(IO::BinaryWriter& writer) {
        for (size_t i = 0; i < m_definitions.size(); ++i) {
            const auto& def = m_definitions[i];

            // Calculate offsets
            uint32_t vd_next = (i == m_definitions.size() - 1) ? 0 : (sizeof(Model::Elf_Verdef) + def.auxNames.size() * sizeof(Model::Elf_Verdaux));
            uint32_t vd_aux = sizeof(Model::Elf_Verdef);

            Model::Elf_Verdef verdef{};
            verdef.vd_version = 1;
            verdef.vd_flags = def.flags;
            verdef.vd_ndx = def.ndx;
            verdef.vd_cnt = static_cast<uint16_t>(def.auxNames.size());
            verdef.vd_hash = def.hash;
            verdef.vd_aux = vd_aux;
            verdef.vd_next = vd_next;

            auto res = writer.Write(verdef);
            if (!res.IsOk()) return res;

            for (size_t j = 0; j < def.auxNames.size(); ++j) {
                Model::Elf_Verdaux verdaux{};
                verdaux.vda_name = m_dynstr.AddString(def.auxNames[j]); // Already added but returns offset
                verdaux.vda_next = (j == def.auxNames.size() - 1) ? 0 : sizeof(Model::Elf_Verdaux);

                res = writer.Write(verdaux);
                if (!res.IsOk()) return res;
            }
        }
        return Common::Result::Ok();
    }

    uint64_t VersionDefinitionBuilder::GetSize() const {
        uint64_t size = 0;
        for (const auto& def : m_definitions) {
            size += sizeof(Model::Elf_Verdef);
            size += def.auxNames.size() * sizeof(Model::Elf_Verdaux);
        }
        return size;
    }

}
