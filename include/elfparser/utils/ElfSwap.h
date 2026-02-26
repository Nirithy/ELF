#pragma once
#include "elfparser/model/ElfStructures.h"
#include "elfparser/utils/Endian.h"

namespace ElfParser::Utils {

    inline void Swap(Model::Elf64_Ehdr& header) {
        header.e_type = Swap(header.e_type);
        header.e_machine = Swap(header.e_machine);
        header.e_version = Swap(header.e_version);
        header.e_entry = Swap(header.e_entry);
        header.e_phoff = Swap(header.e_phoff);
        header.e_shoff = Swap(header.e_shoff);
        header.e_flags = Swap(header.e_flags);
        header.e_ehsize = Swap(header.e_ehsize);
        header.e_phentsize = Swap(header.e_phentsize);
        header.e_phnum = Swap(header.e_phnum);
        header.e_shentsize = Swap(header.e_shentsize);
        header.e_shnum = Swap(header.e_shnum);
        header.e_shstrndx = Swap(header.e_shstrndx);
    }

    inline void Swap(Model::Elf64_Phdr& phdr) {
        phdr.p_type = Swap(phdr.p_type);
        phdr.p_flags = Swap(phdr.p_flags);
        phdr.p_offset = Swap(phdr.p_offset);
        phdr.p_vaddr = Swap(phdr.p_vaddr);
        phdr.p_paddr = Swap(phdr.p_paddr);
        phdr.p_filesz = Swap(phdr.p_filesz);
        phdr.p_memsz = Swap(phdr.p_memsz);
        phdr.p_align = Swap(phdr.p_align);
    }

    inline void Swap(Model::Elf64_Shdr& shdr) {
        shdr.sh_name = Swap(shdr.sh_name);
        shdr.sh_type = Swap(shdr.sh_type);
        shdr.sh_flags = Swap(shdr.sh_flags);
        shdr.sh_addr = Swap(shdr.sh_addr);
        shdr.sh_offset = Swap(shdr.sh_offset);
        shdr.sh_size = Swap(shdr.sh_size);
        shdr.sh_link = Swap(shdr.sh_link);
        shdr.sh_info = Swap(shdr.sh_info);
        shdr.sh_addralign = Swap(shdr.sh_addralign);
        shdr.sh_entsize = Swap(shdr.sh_entsize);
    }
}
