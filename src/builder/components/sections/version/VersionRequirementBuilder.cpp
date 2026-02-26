#include "elfparser/builder/components/sections/version/VersionRequirementBuilder.h"
#include "elfparser/io/BinaryWriter.h"

namespace ElfParser::Builder::Components {

    VersionRequirementBuilder::VersionRequirementBuilder(StringTableBuilder& dynstr, const std::string& name)
        : m_dynstr(dynstr) {
        SetName(name);
        SetType(Model::ElfSectionType::GnuVerNeed);
        SetEntSize(0);
        SetAddralign(4);
        SetInfo(0);
    }

    void VersionRequirementBuilder::AddRequirement(const std::string& filename, const std::vector<VersionNeedAuxEntry>& auxEntries) {
        m_requirements.push_back({filename, auxEntries});
        SetInfo(static_cast<uint32_t>(m_requirements.size()));

        m_dynstr.AddString(filename);
        for(const auto& aux : auxEntries) {
            m_dynstr.AddString(aux.name);
        }
    }

    Common::Result VersionRequirementBuilder::Write(IO::BinaryWriter& writer) {
        for (size_t i = 0; i < m_requirements.size(); ++i) {
            const auto& req = m_requirements[i];

            uint32_t vn_next = (i == m_requirements.size() - 1) ? 0 : (sizeof(Model::Elf_Verneed) + req.auxEntries.size() * sizeof(Model::Elf_Vernaux));
            uint32_t vn_aux = sizeof(Model::Elf_Verneed);

            Model::Elf_Verneed verneed{};
            verneed.vn_version = 1;
            verneed.vn_cnt = static_cast<uint16_t>(req.auxEntries.size());
            verneed.vn_file = m_dynstr.AddString(req.filename);
            verneed.vn_aux = vn_aux;
            verneed.vn_next = vn_next;

            auto res = writer.Write(verneed);
            if (!res.IsOk()) return res;

            for (size_t j = 0; j < req.auxEntries.size(); ++j) {
                const auto& aux = req.auxEntries[j];
                Model::Elf_Vernaux vernaux{};
                vernaux.vna_hash = aux.hash;
                vernaux.vna_flags = aux.flags;
                vernaux.vna_other = aux.other;
                vernaux.vna_name = m_dynstr.AddString(aux.name);
                vernaux.vna_next = (j == req.auxEntries.size() - 1) ? 0 : sizeof(Model::Elf_Vernaux);

                res = writer.Write(vernaux);
                if (!res.IsOk()) return res;
            }
        }
        return Common::Result::Ok();
    }

    uint64_t VersionRequirementBuilder::GetSize() const {
        uint64_t size = 0;
        for (const auto& req : m_requirements) {
            size += sizeof(Model::Elf_Verneed);
            size += req.auxEntries.size() * sizeof(Model::Elf_Vernaux);
        }
        return size;
    }

}
