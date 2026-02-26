#include "TestFramework.h"
#include "elfparser/parser/ElfParser.h"
#include <fstream>
#include <vector>
#include <cstdio>

void CreateDummyElf(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    // ELF Header (64-bit, Little Endian)
    // 00-03: Magic
    file.write("\x7f\x45\x4c\x46", 4);
    // 04: Class (2 = 64-bit)
    file.put(2);
    // 05: Data (1 = Little Endian)
    file.put(1);
    // 06: Version (1)
    file.put(1);
    // 07: OS ABI (0 = SystemV)
    file.put(0);
    // 08: ABI Version (0)
    file.put(0);
    // 09-15: Padding
    for(int i=0; i<7; ++i) file.put(0);

    // 16: Type (2 = Exec)
    uint16_t type = 2; file.write((char*)&type, 2);
    // 18: Machine (62 = x86_64)
    uint16_t machine = 62; file.write((char*)&machine, 2);
    // 20: Version (1)
    uint32_t version = 1; file.write((char*)&version, 4);
    // 24: Entry (0x400000)
    uint64_t entry = 0x400000; file.write((char*)&entry, 8);
    // 32: PhOff (64 bytes)
    uint64_t phoff = 64; file.write((char*)&phoff, 8);
    // 40: ShOff (0)
    uint64_t shoff = 0; file.write((char*)&shoff, 8);
    // 48: Flags (0)
    uint32_t flags = 0; file.write((char*)&flags, 4);
    // 52: EhSize (64)
    uint16_t ehsize = 64; file.write((char*)&ehsize, 2);
    // 54: PhEntSize (56)
    uint16_t phentsize = 56; file.write((char*)&phentsize, 2);
    // 56: PhNum (1)
    uint16_t phnum = 1; file.write((char*)&phnum, 2);
    // 58: ShEntSize (64)
    uint16_t shentsize = 64; file.write((char*)&shentsize, 2);
    // 60: ShNum (0)
    uint16_t shnum = 0; file.write((char*)&shnum, 2);
    // 62: ShStrNdx (0)
    uint16_t shstrndx = 0; file.write((char*)&shstrndx, 2);

    // Program Header (1 entry)
    // 00: Type (1 = Load)
    uint32_t p_type = 1; file.write((char*)&p_type, 4);
    // 04: Flags (5 = RX)
    uint32_t p_flags = 5; file.write((char*)&p_flags, 4);
    // 08: Offset (0)
    uint64_t p_offset = 0; file.write((char*)&p_offset, 8);
    // 16: VAddr (0x400000)
    uint64_t p_vaddr = 0x400000; file.write((char*)&p_vaddr, 8);
    // 24: PAddr (0x400000)
    uint64_t p_paddr = 0x400000; file.write((char*)&p_paddr, 8);
    // 32: FileSz (120) - Header + Phdr
    uint64_t p_filesz = 120; file.write((char*)&p_filesz, 8);
    // 40: MemSz (120)
    uint64_t p_memsz = 120; file.write((char*)&p_memsz, 8);
    // 48: Align (0x1000)
    uint64_t p_align = 0x1000; file.write((char*)&p_align, 8);

    file.close();
}

TEST_CASE(TestBasicElfParsing) {
    std::string filename = "test_elf.bin";
    CreateDummyElf(filename);

    ElfParser::Parser::ElfParser parser(filename);
    auto res = parser.Parse();

    ASSERT_TRUE(res.IsOk());

    const auto& header = parser.GetHeader();
    ASSERT_EQ(header.e_type, 2); // Exec
    ASSERT_EQ(header.e_machine, 62); // x86_64
    ASSERT_EQ(header.e_phnum, 1);

    const auto& phdrs = parser.GetProgramHeaders();
    ASSERT_EQ(phdrs.size(), 1);
    ASSERT_EQ(phdrs[0].p_type, 1); // Load

    // Verify new accessors (should be empty for this dummy file)
    const auto& syms = parser.GetSymbols();
    ASSERT_EQ(syms.size(), 0);

    const auto& dyns = parser.GetDynamicEntries();
    ASSERT_EQ(dyns.size(), 0);

    const auto& rels = parser.GetRelocations();
    ASSERT_EQ(rels.size(), 0);

    std::remove(filename.c_str());
}
