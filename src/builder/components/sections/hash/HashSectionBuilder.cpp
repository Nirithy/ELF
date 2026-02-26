#include "elfparser/builder/components/sections/hash/HashSectionBuilder.h"
#include "elfparser/io/BinaryWriter.h"

namespace ElfParser::Builder::Components {

    HashSectionBuilder::HashSectionBuilder(const std::string& name) {
        SetName(name);
        SetType(Model::ElfSectionType::Hash);
        SetEntSize(4);
        SetAddralign(8);
    }

    void HashSectionBuilder::SetDimensions(uint32_t nbucket, uint32_t nchain) {
        m_nbucket = nbucket;
        m_nchain = nchain;
    }

    void HashSectionBuilder::SetData(const std::vector<uint32_t>& buckets, const std::vector<uint32_t>& chains) {
        m_buckets = buckets;
        m_chains = chains;
        m_nbucket = static_cast<uint32_t>(buckets.size());
        m_nchain = static_cast<uint32_t>(chains.size());
    }

    Common::Result HashSectionBuilder::Write(IO::BinaryWriter& writer) {
        auto res = writer.Write(m_nbucket);
        if (!res.IsOk()) return res;

        res = writer.Write(m_nchain);
        if (!res.IsOk()) return res;

        res = writer.Write(m_buckets);
        if (!res.IsOk()) return res;

        res = writer.Write(m_chains);
        return res;
    }

    uint64_t HashSectionBuilder::GetSize() const {
        return sizeof(uint32_t) * 2 + (m_buckets.size() + m_chains.size()) * sizeof(uint32_t);
    }

}
