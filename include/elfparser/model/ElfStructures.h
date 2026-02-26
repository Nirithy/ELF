#pragma once

#include <cstdint>
#include "elfparser/common/Types.h"

namespace ElfParser::Model {

    // ELF Magic
    constexpr unsigned char ELFMAG[] = { 0x7f, 'E', 'L', 'F' };
    constexpr int SELFMAG = 4;

    // File Class
    enum class ElfClass : uint8_t {
        None = 0,
        Elf32 = 1,
        Elf64 = 2
    };

    // Data Encoding
    enum class ElfData : uint8_t {
        None = 0,
        Lsb = 1, // Little Endian
        Msb = 2  // Big Endian
    };

    // OS ABI
    enum class ElfOsAbi : uint8_t {
        SystemV = 0,
        HpUx = 1,
        NetBSD = 2,
        Linux = 3,
        Solaris = 6,
        Standalone = 255
    };

    // Object File Type
    enum class ElfType : uint16_t {
        None = 0,
        Rel = 1,
        Exec = 2,
        Dyn = 3,
        Core = 4
    };

    // Machine Architecture (Partial List)
    enum class ElfMachine : uint16_t {
        None = 0,
        X86 = 3,
        MIPS = 8,
        PPC = 20,
        ARM = 40,
        X86_64 = 62,
        AArch64 = 183
    };

    #pragma pack(push, 1)

    // ELF Header (64-bit)
    struct Elf64_Ehdr {
        unsigned char e_ident[16]; /* Magic number and other info */
        uint16_t e_type;           /* Object file type */
        uint16_t e_machine;        /* Architecture */
        uint32_t e_version;        /* Object file version */
        uint64_t e_entry;          /* Entry point virtual address */
        uint64_t e_phoff;          /* Program header table file offset */
        uint64_t e_shoff;          /* Section header table file offset */
        uint32_t e_flags;          /* Processor-specific flags */
        uint16_t e_ehsize;         /* ELF header size in bytes */
        uint16_t e_phentsize;      /* Program header table entry size */
        uint16_t e_phnum;          /* Program header table entry count */
        uint16_t e_shentsize;      /* Section header table entry size */
        uint16_t e_shnum;          /* Section header table entry count */
        uint16_t e_shstrndx;       /* Section header string table index */
    };

    // Program Header (64-bit)
    struct Elf64_Phdr {
        uint32_t p_type;   /* Segment type */
        uint32_t p_flags;  /* Segment flags */
        uint64_t p_offset; /* Segment file offset */
        uint64_t p_vaddr;  /* Segment virtual address */
        uint64_t p_paddr;  /* Segment physical address */
        uint64_t p_filesz; /* Segment size in file */
        uint64_t p_memsz;  /* Segment size in memory */
        uint64_t p_align;  /* Segment alignment */
    };

    // Section Header (64-bit)
    struct Elf64_Shdr {
        uint32_t sh_name;      /* Section name (string tbl index) */
        uint32_t sh_type;      /* Section type */
        uint64_t sh_flags;     /* Section flags */
        uint64_t sh_addr;      /* Section virtual addr at execution */
        uint64_t sh_offset;    /* Section file offset */
        uint64_t sh_size;      /* Section size in bytes */
        uint32_t sh_link;      /* Link to another section */
        uint32_t sh_info;      /* Additional section information */
        uint64_t sh_addralign; /* Section alignment */
        uint64_t sh_entsize;   /* Entry size if section holds table */
    };

    #pragma pack(pop)

    // Segment Types
    enum class ElfSegmentType : uint32_t {
        Null = 0,
        Load = 1,
        Dynamic = 2,
        Interp = 3,
        Note = 4,
        ShLib = 5,
        Phdr = 6,
        Tls = 7
    };

    // Section Types
    enum class ElfSectionType : uint32_t {
        Null = 0,
        Progbits = 1,
        Symtab = 2,
        Strtab = 3,
        Rela = 4,
        Hash = 5,
        Dynamic = 6,
        Note = 7,
        Nobits = 8,
        Rel = 9,
        Shlib = 10,
        Dynsym = 11
    };

}
