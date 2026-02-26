#pragma once
#include "elfparser/model/ElfStructures.h"
#include "elfparser/utils/Endian.h"

namespace ElfParser::Utils {

    // --- Elf32_Ehdr ---
    inline void Swap(Model::Elf32_Ehdr& header) {
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

    // --- Elf64_Ehdr ---
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

    // --- Elf32_Phdr ---
    inline void Swap(Model::Elf32_Phdr& phdr) {
        phdr.p_type = Swap(phdr.p_type);
        phdr.p_offset = Swap(phdr.p_offset);
        phdr.p_vaddr = Swap(phdr.p_vaddr);
        phdr.p_paddr = Swap(phdr.p_paddr);
        phdr.p_filesz = Swap(phdr.p_filesz);
        phdr.p_memsz = Swap(phdr.p_memsz);
        phdr.p_flags = Swap(phdr.p_flags);
        phdr.p_align = Swap(phdr.p_align);
    }

    // --- Elf64_Phdr ---
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

    // --- Elf32_Shdr ---
    inline void Swap(Model::Elf32_Shdr& shdr) {
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

    // --- Elf64_Shdr ---
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

    // --- Elf32_Sym ---
    inline void Swap(Model::Elf32_Sym& sym) {
        sym.st_name = Swap(sym.st_name);
        sym.st_value = Swap(sym.st_value);
        sym.st_size = Swap(sym.st_size);
        sym.st_shndx = Swap(sym.st_shndx);
    }

    // --- Elf64_Sym ---
    inline void Swap(Model::Elf64_Sym& sym) {
        sym.st_name = Swap(sym.st_name);
        sym.st_shndx = Swap(sym.st_shndx);
        sym.st_value = Swap(sym.st_value);
        sym.st_size = Swap(sym.st_size);
    }

    // --- Elf32_Dyn ---
    inline void Swap(Model::Elf32_Dyn& dyn) {
        dyn.d_tag = Swap(dyn.d_tag);
        dyn.d_un.d_val = Swap(dyn.d_un.d_val);
    }

    // --- Elf64_Dyn ---
    inline void Swap(Model::Elf64_Dyn& dyn) {
        dyn.d_tag = Swap(dyn.d_tag);
        dyn.d_un.d_val = Swap(dyn.d_un.d_val);
    }

    // --- Elf32_Rel ---
    inline void Swap(Model::Elf32_Rel& rel) {
        rel.r_offset = Swap(rel.r_offset);
        rel.r_info = Swap(rel.r_info);
    }

    // --- Elf32_Rela ---
    inline void Swap(Model::Elf32_Rela& rela) {
        rela.r_offset = Swap(rela.r_offset);
        rela.r_info = Swap(rela.r_info);
        rela.r_addend = Swap(rela.r_addend);
    }

    // --- Elf64_Rel ---
    inline void Swap(Model::Elf64_Rel& rel) {
        rel.r_offset = Swap(rel.r_offset);
        rel.r_info = Swap(rel.r_info);
    }

    // --- Elf64_Rela ---
    inline void Swap(Model::Elf64_Rela& rela) {
        rela.r_offset = Swap(rela.r_offset);
        rela.r_info = Swap(rela.r_info);
        rela.r_addend = Swap(rela.r_addend);
    }

    // --- Elf32_Nhdr ---
    inline void Swap(Model::Elf32_Nhdr& nhdr) {
        nhdr.n_namesz = Swap(nhdr.n_namesz);
        nhdr.n_descsz = Swap(nhdr.n_descsz);
        nhdr.n_type = Swap(nhdr.n_type);
    }

    // --- Elf64_Nhdr ---
    inline void Swap(Model::Elf64_Nhdr& nhdr) {
        nhdr.n_namesz = Swap(nhdr.n_namesz);
        nhdr.n_descsz = Swap(nhdr.n_descsz);
        nhdr.n_type = Swap(nhdr.n_type);
    }

    // --- Elf_Hash ---
    inline void Swap(Model::Elf_Hash& hash) {
        hash.nbucket = Swap(hash.nbucket);
        hash.nchain = Swap(hash.nchain);
    }

    // --- Elf_GnuHash ---
    inline void Swap(Model::Elf_GnuHash& gnuHash) {
        gnuHash.nbuckets = Swap(gnuHash.nbuckets);
        gnuHash.symndx = Swap(gnuHash.symndx);
        gnuHash.maskwords = Swap(gnuHash.maskwords);
        gnuHash.shift2 = Swap(gnuHash.shift2);
    }

    // --- Elf_Verdef ---
    inline void Swap(Model::Elf_Verdef& verdef) {
        verdef.vd_version = Swap(verdef.vd_version);
        verdef.vd_flags = Swap(verdef.vd_flags);
        verdef.vd_ndx = Swap(verdef.vd_ndx);
        verdef.vd_cnt = Swap(verdef.vd_cnt);
        verdef.vd_hash = Swap(verdef.vd_hash);
        verdef.vd_aux = Swap(verdef.vd_aux);
        verdef.vd_next = Swap(verdef.vd_next);
    }

    // --- Elf_Verdaux ---
    inline void Swap(Model::Elf_Verdaux& verdaux) {
        verdaux.vda_name = Swap(verdaux.vda_name);
        verdaux.vda_next = Swap(verdaux.vda_next);
    }

    // --- Elf_Verneed ---
    inline void Swap(Model::Elf_Verneed& verneed) {
        verneed.vn_version = Swap(verneed.vn_version);
        verneed.vn_cnt = Swap(verneed.vn_cnt);
        verneed.vn_file = Swap(verneed.vn_file);
        verneed.vn_aux = Swap(verneed.vn_aux);
        verneed.vn_next = Swap(verneed.vn_next);
    }

    // --- Elf_Vernaux ---
    inline void Swap(Model::Elf_Vernaux& vernaux) {
        vernaux.vna_hash = Swap(vernaux.vna_hash);
        vernaux.vna_flags = Swap(vernaux.vna_flags);
        vernaux.vna_other = Swap(vernaux.vna_other);
        vernaux.vna_name = Swap(vernaux.vna_name);
        vernaux.vna_next = Swap(vernaux.vna_next);
    }
}
