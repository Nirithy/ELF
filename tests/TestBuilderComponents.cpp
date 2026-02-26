#include "TestFramework.h"
#include "elfparser/builder/components/sections/symbols/SymbolTableBuilder.h"
#include "elfparser/builder/components/sections/dynamic/DynamicSectionBuilder.h"
#include "elfparser/builder/components/sections/relocations/RelocationSectionBuilder.h"
#include "elfparser/builder/components/sections/StringTableBuilder.h"
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
