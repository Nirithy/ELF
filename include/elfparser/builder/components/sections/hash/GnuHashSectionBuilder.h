#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    class GnuHashSectionBuilder : public SectionBuilder {
    public:
        explicit GnuHashSectionBuilder(const std::string& name = ".gnu.hash");

        void SetHeader(uint32_t nbuckets, uint32_t symndx, uint32_t maskwords, uint32_t shift2);
        void SetBloomFilter(const std::vector<uint64_t>& bloom);
        void SetBuckets(const std::vector<uint32_t>& buckets);
        void SetHashValues(const std::vector<uint32_t>& hashValues);

        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        uint32_t m_nbuckets = 0;
        uint32_t m_symndx = 0;
        uint32_t m_maskwords = 0;
        uint32_t m_shift2 = 0;

        std::vector<uint64_t> m_bloomFilter;
        std::vector<uint32_t> m_buckets;
        std::vector<uint32_t> m_hashValues;
    };

}
