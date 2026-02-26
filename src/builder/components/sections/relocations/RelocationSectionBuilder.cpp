#include "elfparser/builder/components/sections/relocations/RelocationSectionBuilder.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Builder::Components {

    RelocationSectionBuilder::RelocationSectionBuilder(const std::string& name) {
        SetName(name);
        SetType(Model::ElfSectionType::Rela);
        SetEntSize(sizeof(Model::Elf64_Rela));
        // Link (symbol table) and Info (target section) must be set later
    }

    void RelocationSectionBuilder::AddRelocation(const Model::Elf64_Rela& rela) {
        m_relocations.push_back(rela);
    }

    void RelocationSectionBuilder::AddRelocation(uint64_t offset, uint32_t type, uint32_t symIdx, int64_t addend) {
        Model::Elf64_Rela rela;
        rela.r_offset = offset;
        rela.r_info = MakeInfo(symIdx, type);
        rela.r_addend = addend;
        AddRelocation(rela);
    }

    Common::Result RelocationSectionBuilder::Write(IO::BinaryWriter& writer) {
        for (auto rela : m_relocations) {
            if (writer.ShouldSwap()) {
                Utils::Swap(rela);
            }
            auto result = writer.Write(&rela, sizeof(rela));
            if (!result.IsOk()) {
                return result;
            }
        }
        return Common::Result::Ok();
    }

    uint64_t RelocationSectionBuilder::GetSize() const {
        return m_relocations.size() * sizeof(Model::Elf64_Rela);
    }

}
