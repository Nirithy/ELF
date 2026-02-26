#pragma once

#include <vector>
#include <string>
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Builder::Components {

    class HashSectionBuilder : public SectionBuilder {
    public:
        explicit HashSectionBuilder(const std::string& name = ".hash");

        // Set the number of buckets and chains
        void SetDimensions(uint32_t nbucket, uint32_t nchain);

        // Set the raw bucket and chain data
        void SetData(const std::vector<uint32_t>& buckets, const std::vector<uint32_t>& chains);

        // SectionBuilder implementation
        Common::Result Write(IO::BinaryWriter& writer) override;
        uint64_t GetSize() const override;

    private:
        uint32_t m_nbucket = 0;
        uint32_t m_nchain = 0;
        std::vector<uint32_t> m_buckets;
        std::vector<uint32_t> m_chains;
    };

}
