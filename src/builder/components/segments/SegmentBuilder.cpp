#include "elfparser/builder/components/segments/SegmentBuilder.h"
#include "elfparser/builder/components/segments/calculators/DefaultSegmentCalculator.h"

namespace ElfParser::Builder::Components {

    SegmentBuilder::SegmentBuilder(Model::ElfSegmentType type) {
        m_header.p_type = static_cast<uint32_t>(type);
        m_header.p_flags = 0;
        m_header.p_offset = 0;
        m_header.p_vaddr = 0;
        m_header.p_paddr = 0;
        m_header.p_filesz = 0;
        m_header.p_memsz = 0;
        m_header.p_align = 0x1000; // Default page alignment

        m_calculator = std::make_unique<Segments::Calculators::DefaultSegmentCalculator>();
    }

    SegmentBuilder::~SegmentBuilder() = default;

    void SegmentBuilder::SetFlags(uint32_t flags) {
        m_header.p_flags = flags;
    }

    void SegmentBuilder::SetVAddr(uint64_t vaddr) {
        m_header.p_vaddr = vaddr;
    }

    void SegmentBuilder::SetPAddr(uint64_t paddr) {
        m_header.p_paddr = paddr;
    }

    void SegmentBuilder::SetAlign(uint64_t align) {
        m_header.p_align = align;
    }

    void SegmentBuilder::SetFileSize(uint64_t fileSize) {
        m_header.p_filesz = fileSize;
    }

    void SegmentBuilder::SetMemSize(uint64_t memSize) {
        m_header.p_memsz = memSize;
    }

    void SegmentBuilder::AddSection(SectionBuilder* section) {
        if (section) {
            m_sections.push_back(section);
        }
    }

    const std::vector<SectionBuilder*>& SegmentBuilder::GetSections() const {
        return m_sections;
    }

    void SegmentBuilder::SetCalculator(std::unique_ptr<Segments::Calculators::ISegmentCalculator> calculator) {
        if (calculator) {
            m_calculator = std::move(calculator);
        }
    }

    void SegmentBuilder::Finalize(Layout::LayoutManager& layout) {
        if (m_calculator) {
            m_calculator->Calculate(*this, layout);
        }
    }

    const Model::Elf64_Phdr& SegmentBuilder::GetHeader() const {
        return m_header;
    }

    Model::Elf64_Phdr& SegmentBuilder::GetHeaderRef() {
        return m_header;
    }

    Model::ElfSegmentType SegmentBuilder::GetType() const {
        return static_cast<Model::ElfSegmentType>(m_header.p_type);
    }

}
