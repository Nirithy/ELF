#include "elfparser/builder/components/sections/SectionBuilder.h"

namespace ElfParser::Builder::Components {

    void SectionBuilder::SetName(const std::string& name) {
        m_name = name;
    }

    void SectionBuilder::SetType(Model::ElfSectionType type) {
        m_header.sh_type = static_cast<uint32_t>(type);
    }

    void SectionBuilder::SetFlags(uint64_t flags) {
        m_header.sh_flags = flags;
    }

    void SectionBuilder::SetAddr(uint64_t addr) {
        m_header.sh_addr = addr;
    }

    void SectionBuilder::SetAddralign(uint64_t align) {
        m_header.sh_addralign = align;
    }

    void SectionBuilder::SetLink(uint32_t link) {
        m_header.sh_link = link;
    }

    void SectionBuilder::SetInfo(uint32_t info) {
        m_header.sh_info = info;
    }

    void SectionBuilder::SetEntSize(uint64_t entsize) {
        m_header.sh_entsize = entsize;
    }

    const std::string& SectionBuilder::GetName() const {
        return m_name;
    }

    Model::Elf64_Shdr& SectionBuilder::GetHeader() {
        return m_header;
    }

    const Model::Elf64_Shdr& SectionBuilder::GetHeader() const {
        return m_header;
    }

    void SectionBuilder::UpdateHeader(uint64_t offset, uint64_t size) {
        m_header.sh_offset = offset;
        m_header.sh_size = size;
    }

}
