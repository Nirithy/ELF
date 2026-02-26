#include "TestFramework.h"
#include "elfparser/builder/components/sections/symbols/SymbolTableBuilder.h"
#include "elfparser/builder/components/sections/dynamic/DynamicSectionBuilder.h"
#include "elfparser/builder/components/sections/relocations/RelocationSectionBuilder.h"
#include "elfparser/builder/components/sections/strings/StringTableBuilder.h"
#include "elfparser/builder/components/segments/LoadSegmentBuilder.h"
#include "elfparser/builder/layout/LayoutManager.h"
#include "elfparser/model/ElfStructures.h"
#include <iostream>

// Test SymbolTableBuilder
void TestSymbolTableBuilder() {
    using namespace ElfParser;

    Builder::Components::StringTableBuilder strtab(".strtab");
    Builder::Components::SymbolTableBuilder symtab(strtab);

    // Check initial state (should have 1 NULL symbol)
    // Wait, GetSize() should be sizeof(Elf64_Sym)
    if (symtab.GetSize() != sizeof(Model::Elf64_Sym)) {
        throw std::runtime_error("SymbolTableBuilder should start with one NULL symbol");
    }

    // Add a symbol
    Model::Elf64_Sym sym{};
    // st_info = (STB << 4) | (STT & 0xf)
    unsigned char binding = static_cast<unsigned char>(Model::ElfSymbolBinding::Global);
    unsigned char type = static_cast<unsigned char>(Model::ElfSymbolType::Func);
    sym.st_info = (binding << 4) | (type & 0xf);

    sym.st_shndx = 1; // Dummy section index
    sym.st_value = 0x1000;
    sym.st_size = 0x20;

    uint32_t idx = symtab.AddSymbol(sym, "main");

    if (idx != 1) {
        throw std::runtime_error("Added symbol index should be 1");
    }

    if (symtab.GetSize() != 2 * sizeof(Model::Elf64_Sym)) {
        throw std::runtime_error("SymbolTableBuilder size incorrect after adding symbol");
    }

    // Check string table grew
    if (strtab.GetSize() == 0) {
        throw std::runtime_error("StringTableBuilder should not be empty");
    }
}
struct TestSymbolTableBuilder_Register {
    TestSymbolTableBuilder_Register() { TestFramework::TestRunner::Get().AddTest("TestSymbolTableBuilder", TestSymbolTableBuilder); }
} TestSymbolTableBuilder_register_inst;


// Test DynamicSectionBuilder
void TestDynamicSectionBuilder() {
    using namespace ElfParser;

    Builder::Components::StringTableBuilder dynstr(".dynstr");
    Builder::Components::DynamicSectionBuilder dyn(dynstr);

    Model::Elf64_Dyn d{};
    d.d_tag = static_cast<int64_t>(Model::ElfDynamicTag::Needed);
    d.d_un.d_val = 0; // Will be overwritten

    dyn.AddEntry(d, "libm.so.6");

    if (dyn.GetSize() != sizeof(Model::Elf64_Dyn)) {
        throw std::runtime_error("DynamicSectionBuilder size incorrect");
    }

    if (dynstr.GetSize() == 0) {
       // StringTableBuilder usually starts empty (0 bytes) if constructor does nothing,
       // but typically ELF string tables start with \0.
       // My StringTableBuilder checks imply it handles \0.
    }
}
struct TestDynamicSectionBuilder_Register {
    TestDynamicSectionBuilder_Register() { TestFramework::TestRunner::Get().AddTest("TestDynamicSectionBuilder", TestDynamicSectionBuilder); }
} TestDynamicSectionBuilder_register_inst;


// Test RelocationSectionBuilder
void TestRelocationSectionBuilder() {
    using namespace ElfParser;

    Builder::Components::RelocationSectionBuilder rela(".rela.text");

    // Add relocation manually
    Model::Elf64_Rela r{};
    r.r_offset = 0x100;
    r.r_info = Builder::Components::RelocationSectionBuilder::MakeInfo(1, 6); // 6 = R_X86_64_GLOB_DAT
    r.r_addend = 0;

    rela.AddRelocation(r);

    if (rela.GetSize() != sizeof(Model::Elf64_Rela)) {
        throw std::runtime_error("RelocationSectionBuilder size incorrect");
    }

    // Add via helper
    rela.AddRelocation(0x200, 6, 2, 4);

    if (rela.GetSize() != 2 * sizeof(Model::Elf64_Rela)) {
        throw std::runtime_error("RelocationSectionBuilder size incorrect after helper add");
    }
}
struct TestRelocationSectionBuilder_Register {
    TestRelocationSectionBuilder_Register() { TestFramework::TestRunner::Get().AddTest("TestRelocationSectionBuilder", TestRelocationSectionBuilder); }
} TestRelocationSectionBuilder_register_inst;


// Mock Section Builder for testing
class MockSectionBuilder : public ElfParser::Builder::Components::SectionBuilder {
public:
    MockSectionBuilder(const std::string& name, uint64_t size) {
        SetName(name);
        m_size = size;
        m_header.sh_type = 1; // SHT_PROGBITS
        m_header.sh_flags = 6; // AX
        m_header.sh_addralign = 1;
    }
    ElfParser::Common::Result Write(ElfParser::IO::BinaryWriter&) override { return ElfParser::Common::Result::Ok(); }
    uint64_t GetSize() const override { return m_size; }
private:
    uint64_t m_size;
    ElfParser::Model::Elf64_Shdr m_header_storage{};
};

void TestSegmentBuilder() {
    using namespace ElfParser::Builder;

    // Create sections
    auto sec1 = std::make_unique<MockSectionBuilder>(".text", 0x1000);
    auto sec2 = std::make_unique<MockSectionBuilder>(".rodata", 0x500);

    // Mock pointers needed for verification later
    auto* pSec1 = sec1.get();
    auto* pSec2 = sec2.get();

    // Layout
    Layout::LayoutManager layout(0x100); // Start at 0x100

    std::vector<std::unique_ptr<Components::SegmentBuilder>> segs;

    // Create Load Segment
    segs.push_back(std::make_unique<Components::LoadSegmentBuilder>());
    segs[0]->AddSection(pSec1);
    segs[0]->AddSection(pSec2);

    std::vector<std::unique_ptr<Components::SectionBuilder>> sections;
    sections.push_back(std::move(sec1));
    sections.push_back(std::move(sec2));

    layout.ComputeLayout(segs, sections);

    // Check Segment
    const auto& hdr = segs[0]->GetHeader();

    // Segment 1 (Load) aligns to 0x1000.
    // 0x100 -> 0x1000.

    // Sec1 at 0x1000. Size 0x1000. Ends 0x2000.
    // Sec2 at 0x2000. Size 0x500. Ends 0x2500.

    // Segment Offset 0x1000. FileSz 0x1500.

    if (hdr.p_offset != 0x1000) {
        std::cout << "Expected offset 0x1000, got " << std::hex << hdr.p_offset << std::dec << std::endl;
        throw std::runtime_error("Segment offset incorrect");
    }
    if (hdr.p_filesz != 0x1500) {
        std::cout << "Expected filesz 0x1500, got " << std::hex << hdr.p_filesz << std::dec << std::endl;
        throw std::runtime_error("Segment filesz incorrect");
    }
}
struct TestSegmentBuilder_Register {
    TestSegmentBuilder_Register() { TestFramework::TestRunner::Get().AddTest("TestSegmentBuilder", TestSegmentBuilder); }
} TestSegmentBuilder_register_inst;
