#include "elfparser/builder/components/headers/ShdrBuilder.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Builder::Components {

    void ShdrBuilder::AddSection(const Model::Elf64_Shdr& shdr) {
        m_sections.push_back(shdr);
    }

    const std::vector<Model::Elf64_Shdr>& ShdrBuilder::GetSections() const {
        return m_sections;
    }

    std::vector<Model::Elf64_Shdr>& ShdrBuilder::GetSections() {
        return m_sections;
    }

    Common::Result ShdrBuilder::Write(IO::BinaryWriter& writer) {
        for (auto shdr : m_sections) {
            if (writer.ShouldSwap()) {
                Utils::Swap(shdr);
            }
            auto res = writer.Write(&shdr, sizeof(shdr));
            if (!res.IsOk()) return res;
        }
        return Common::Result::Ok();
    }

    uint16_t ShdrBuilder::GetCount() const {
        return static_cast<uint16_t>(m_sections.size());
    }

    uint64_t ShdrBuilder::GetSize() const {
        return m_sections.size() * sizeof(Model::Elf64_Shdr);
    }

}
