#pragma once

#include <vector>
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryWriter.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Builder::Components {

    class PhdrBuilder {
    public:
        void AddSegment(const Model::Elf64_Phdr& phdr);
        const std::vector<Model::Elf64_Phdr>& GetSegments() const;

        Common::Result Write(IO::BinaryWriter& writer);

        uint16_t GetCount() const;
        uint64_t GetSize() const;

    private:
        std::vector<Model::Elf64_Phdr> m_segments;
    };

}
