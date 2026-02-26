#include "elfparser/parser/components/sections/hash/HashSectionParser.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser::Components {

    Common::Result HashSectionParser::Parse(IO::BinaryReader& reader,
                                            const Model::Elf64_Shdr& shdr,
                                            Model::Elf_Hash& header,
                                            std::vector<uint32_t>& buckets,
                                            std::vector<uint32_t>& chains) {

        if (!reader.Seek(shdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to hash section offset");
        }

        // Read Header
        if (!reader.Read(header)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Hash Header");
        }
        if (reader.ShouldSwap()) {
            Utils::Swap(header);
        }

        // Read Buckets
        buckets.resize(header.nbucket);
        for (uint32_t i = 0; i < header.nbucket; ++i) {
            if (!reader.Read(buckets[i])) {
                 return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Hash Buckets");
            }
        }

        // Read Chains
        chains.resize(header.nchain);
        for (uint32_t i = 0; i < header.nchain; ++i) {
            if (!reader.Read(chains[i])) {
                 return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Hash Chains");
            }
        }

        return Common::Result::Ok();
    }
}
