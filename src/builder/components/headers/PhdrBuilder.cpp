#include "elfparser/builder/components/headers/PhdrBuilder.h"
#include "elfparser/utils/ElfSwap.h"

namespace ElfParser::Builder::Components {

    void PhdrBuilder::AddSegment(const Model::Elf64_Phdr& phdr) {
        m_segments.push_back(phdr);
    }

    const std::vector<Model::Elf64_Phdr>& PhdrBuilder::GetSegments() const {
        return m_segments;
    }

    Common::Result PhdrBuilder::Write(IO::BinaryWriter& writer) {
        for (auto phdr : m_segments) {
            if (writer.ShouldSwap()) {
                Utils::Swap(phdr);
            }
            auto res = writer.Write(&phdr, sizeof(phdr));
            if (!res.IsOk()) return res;
        }
        return Common::Result::Ok();
    }

    uint16_t PhdrBuilder::GetCount() const {
        return static_cast<uint16_t>(m_segments.size());
    }

    uint64_t PhdrBuilder::GetSize() const {
        return m_segments.size() * sizeof(Model::Elf64_Phdr);
    }

}
