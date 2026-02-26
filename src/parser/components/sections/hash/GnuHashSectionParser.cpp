#include "elfparser/parser/components/sections/hash/GnuHashSectionParser.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/utils/Logger.h"
#include "elfparser/model/enums/ElfClass.h"

namespace ElfParser::Parser::Components {

    Common::Result GnuHashSectionParser::Parse(IO::BinaryReader& reader,
                                               const Model::Elf64_Ehdr& ehdr,
                                               const Model::Elf64_Shdr& shdr,
                                               Model::Elf_GnuHash& header,
                                               std::vector<uint64_t>& bloomFilter,
                                               std::vector<uint32_t>& buckets,
                                               std::vector<uint32_t>& chain) {

        if (!reader.Seek(shdr.sh_offset)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to GNU hash section offset");
        }

        // Read Header
        if (!reader.Read(header)) {
             return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read GNU Hash Header");
        }
        if (reader.ShouldSwap()) {
            Utils::Swap(header);
        }

        // Determine Bloom Filter word size
        // e_ident[4] is EI_CLASS
        uint8_t elfClass = ehdr.e_ident[4];
        uint32_t wordSize = (elfClass == static_cast<uint8_t>(Model::ElfClass::Elf64)) ? 8 : 4;

        bloomFilter.resize(header.maskwords);
        for (uint32_t i = 0; i < header.maskwords; ++i) {
            if (wordSize == 8) {
                uint64_t val;
                if (!reader.Read(val)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Bloom Filter Word (64-bit)");
                bloomFilter[i] = val;
            } else {
                uint32_t val;
                if (!reader.Read(val)) return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Bloom Filter Word (32-bit)");
                bloomFilter[i] = static_cast<uint64_t>(val);
            }
        }

        // Read Buckets (always 32-bit)
        buckets.resize(header.nbuckets);
        for (uint32_t i = 0; i < header.nbuckets; ++i) {
            if (!reader.Read(buckets[i])) {
                 return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read GNU Hash Buckets");
            }
        }

        // Calculate remaining size for Chain
        std::streampos currentPos = reader.Tell();
        std::streampos endPos = shdr.sh_offset + shdr.sh_size;

        if (currentPos > endPos) {
            return Common::Result::Fail(Common::StatusCode::InvalidFormat, "GNU Hash section overrun");
        }

        uint64_t remainingBytes = static_cast<uint64_t>(endPos - currentPos);
        if (remainingBytes % 4 != 0) {
             Utils::Logger::Warn("GNU Hash chain size is not a multiple of 4 bytes.");
        }
        uint64_t chainSize = remainingBytes / 4;

        chain.resize(chainSize);
        for (uint64_t i = 0; i < chainSize; ++i) {
            if (!reader.Read(chain[i])) {
                 return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read GNU Hash Chain");
            }
        }

        return Common::Result::Ok();
    }
}
