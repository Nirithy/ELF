#include "elfparser/parser/components/sections/version/VersionRequirementParser.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser::Components {

    Common::Result VersionRequirementParser::Parse(IO::BinaryReader& reader,
                                                   const Model::Elf64_Shdr& shdr,
                                                   std::vector<VersionRequirementEntry>& requirements) {

        if (!reader.Seek(shdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to version requirement section offset");
        }

        uint32_t numNeeds = shdr.sh_info;
        requirements.reserve(numNeeds);

        uint64_t currentNeedOffset = shdr.sh_offset;

        for (uint32_t i = 0; i < numNeeds; ++i) {
            if (!reader.Seek(currentNeedOffset)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to VerNeed entry");
            }

            Model::Elf_Verneed verneed;
            if (!reader.Read(verneed)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read VerNeed");
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(verneed);
            }

            VersionRequirementEntry entry;
            entry.need = verneed;

            uint64_t currentAuxOffset = currentNeedOffset + verneed.vn_aux;

            for (uint16_t j = 0; j < verneed.vn_cnt; ++j) {
                if (!reader.Seek(currentAuxOffset)) {
                     return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to VernAux entry");
                }

                Model::Elf_Vernaux aux;
                if (!reader.Read(aux)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read VernAux");
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(aux);
                }
                entry.auxiliaries.push_back(aux);

                if (aux.vna_next == 0) break;
                currentAuxOffset += aux.vna_next;
            }

            requirements.push_back(entry);

            if (verneed.vn_next == 0) break;
            currentNeedOffset += verneed.vn_next;
        }

        return Common::Result::Ok();
    }
}
