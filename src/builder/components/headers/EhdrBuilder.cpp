#include "elfparser/builder/components/headers/EhdrBuilder.h"
#include "elfparser/utils/ElfSwap.h"
#include "elfparser/model/enums/ElfVersion.h"
#include <cstring>

namespace ElfParser::Builder::Components {

    EhdrBuilder::EhdrBuilder() {
        std::memset(&m_header, 0, sizeof(m_header));
        // Set Magic
        std::memcpy(m_header.e_ident, Model::ELFMAG, Model::SELFMAG);
        // Default to ELF64, 2's complement, Native Endian (initially), Current Version, SYSV
        m_header.e_ident[Model::EI_CLASS] = static_cast<unsigned char>(Model::ElfClass::Elf64);
        m_header.e_ident[Model::EI_DATA] = static_cast<unsigned char>(Model::ElfData::Lsb); // Default Lsb
        m_header.e_ident[Model::EI_VERSION] = static_cast<unsigned char>(Model::ElfVersion::Current);
        m_header.e_ident[Model::EI_OSABI] = static_cast<unsigned char>(Model::ElfOsAbi::SystemV);
        m_header.e_ident[Model::EI_ABIVERSION] = 0;

        m_header.e_version = static_cast<uint32_t>(Model::ElfVersion::Current);
        m_header.e_ehsize = sizeof(Model::Elf64_Ehdr);
        m_header.e_phentsize = sizeof(Model::Elf64_Phdr);
        m_header.e_shentsize = sizeof(Model::Elf64_Shdr);
    }

    void EhdrBuilder::SetClass(Model::ElfClass cls) {
        m_header.e_ident[Model::EI_CLASS] = static_cast<unsigned char>(cls);
    }

    void EhdrBuilder::SetData(Model::ElfData data) {
        m_header.e_ident[Model::EI_DATA] = static_cast<unsigned char>(data);
    }

    void EhdrBuilder::SetOsAbi(Model::ElfOsAbi osabi) {
        m_header.e_ident[Model::EI_OSABI] = static_cast<unsigned char>(osabi);
    }

    void EhdrBuilder::SetType(Model::ElfType type) {
        m_header.e_type = static_cast<uint16_t>(type);
    }

    void EhdrBuilder::SetMachine(Model::ElfMachine machine) {
        m_header.e_machine = static_cast<uint16_t>(machine);
    }

    void EhdrBuilder::SetEntry(uint64_t entry) {
        m_header.e_entry = entry;
    }

    void EhdrBuilder::SetFlags(uint32_t flags) {
        m_header.e_flags = flags;
    }

    void EhdrBuilder::UpdateLayout(uint64_t phoff, uint16_t phnum, uint64_t shoff, uint16_t shnum, uint16_t shstrndx) {
        m_header.e_phoff = phoff;
        m_header.e_phnum = phnum;
        m_header.e_shoff = shoff;
        m_header.e_shnum = shnum;
        m_header.e_shstrndx = shstrndx;
    }

    const Model::Elf64_Ehdr& EhdrBuilder::GetHeader() const {
        return m_header;
    }

    Common::Result EhdrBuilder::Write(IO::BinaryWriter& writer) {
        Model::Elf64_Ehdr headerCopy = m_header;

        if (writer.ShouldSwap()) {
            Utils::Swap(headerCopy);
        }

        return writer.Write(&headerCopy, sizeof(headerCopy));
    }

}
