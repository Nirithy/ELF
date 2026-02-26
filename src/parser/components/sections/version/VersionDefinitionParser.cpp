#include "elfparser/parser/components/sections/version/VersionDefinitionParser.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser::Components {

    Common::Result VersionDefinitionParser::Parse(IO::BinaryReader& reader,
                                                  const Model::Elf64_Shdr& shdr,
                                                  std::vector<VersionDefinitionEntry>& definitions) {

        if (!reader.Seek(shdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to version definition section offset");
        }

        uint32_t numDefs = shdr.sh_info;
        definitions.reserve(numDefs);

        uint64_t currentDefOffset = shdr.sh_offset;

        for (uint32_t i = 0; i < numDefs; ++i) {
            if (!reader.Seek(currentDefOffset)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to VerDef entry");
            }

            Model::Elf_Verdef verdef;
            if (!reader.Read(verdef)) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read VerDef");
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(verdef);
            }

            VersionDefinitionEntry entry;
            entry.def = verdef;

            // Parse auxiliaries
            // vd_aux is offset from start of this VerDef
            uint64_t currentAuxOffset = currentDefOffset + verdef.vd_aux;

            // vd_cnt is usually number of aux entries
            for (uint16_t j = 0; j < verdef.vd_cnt; ++j) {
                if (!reader.Seek(currentAuxOffset)) {
                     return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to VerDAux entry");
                }

                Model::Elf_Verdaux aux;
                if (!reader.Read(aux)) {
                    return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read VerDAux");
                }
                if (reader.ShouldSwap()) {
                    Utils::Swap(aux);
                }
                entry.auxiliaries.push_back(aux);

                if (aux.vda_next == 0) break;
                currentAuxOffset += aux.vda_next;
            }

            definitions.push_back(entry);

            if (verdef.vd_next == 0) break;
            currentDefOffset += verdef.vd_next;
        }

        return Common::Result::Ok();
    }
}
