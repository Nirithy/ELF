#include "elfparser/builder/components/sections/hash/GnuHashSectionBuilder.h"
#include "elfparser/io/BinaryWriter.h"

namespace ElfParser::Builder::Components {

    GnuHashSectionBuilder::GnuHashSectionBuilder(const std::string& name) {
        SetName(name);
        SetType(Model::ElfSectionType::GnuHash);
        SetEntSize(4); // Bloom words are variable, so no fixed entsize really. Often 0.
        SetAddralign(8);
    }

    void GnuHashSectionBuilder::SetHeader(uint32_t nbuckets, uint32_t symndx, uint32_t maskwords, uint32_t shift2) {
        m_nbuckets = nbuckets;
        m_symndx = symndx;
        m_maskwords = maskwords;
        m_shift2 = shift2;
    }

    void GnuHashSectionBuilder::SetBloomFilter(const std::vector<uint64_t>& bloom) {
        m_bloomFilter = bloom;
    }

    void GnuHashSectionBuilder::SetBuckets(const std::vector<uint32_t>& buckets) {
        m_buckets = buckets;
    }

    void GnuHashSectionBuilder::SetHashValues(const std::vector<uint32_t>& hashValues) {
        m_hashValues = hashValues;
    }

    Common::Result GnuHashSectionBuilder::Write(IO::BinaryWriter& writer) {
        auto res = writer.Write(m_nbuckets);
        if (!res.IsOk()) return res;

        res = writer.Write(m_symndx);
        if (!res.IsOk()) return res;

        res = writer.Write(m_maskwords);
        if (!res.IsOk()) return res;

        res = writer.Write(m_shift2);
        if (!res.IsOk()) return res;

        // Bloom filter
        res = writer.Write(m_bloomFilter);
        if (!res.IsOk()) return res;

        // Buckets
        res = writer.Write(m_buckets);
        if (!res.IsOk()) return res;

        // Hash Values
        res = writer.Write(m_hashValues);
        return res;
    }

    uint64_t GnuHashSectionBuilder::GetSize() const {
        return 4 * sizeof(uint32_t) +
               m_bloomFilter.size() * sizeof(uint64_t) +
               m_buckets.size() * sizeof(uint32_t) +
               m_hashValues.size() * sizeof(uint32_t);
    }

}
