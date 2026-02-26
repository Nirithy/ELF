#include "TestFramework.h"
#include "elfparser/builder/ElfBuilder.h"
#include "elfparser/builder/components/segments/LoadSegmentBuilder.h"
#include "elfparser/io/BinaryReader.h"
#include "elfparser/model/ElfStructures.h"
#include <fstream>
#include <cstdio>

using namespace ElfParser;

TEST_CASE(TestSimpleBuild) {
    std::string testFile = "test_output.elf";

    // 1. Build
    {
        Builder::ElfBuilder builder(testFile);
        builder.GetHeaderBuilder().SetType(Model::ElfType::Exec);
        builder.GetHeaderBuilder().SetMachine(Model::ElfMachine::X86_64);
        builder.GetHeaderBuilder().SetEntry(0x400000);

        // Add a dummy section
        auto strtab = std::make_unique<Builder::Components::StringTableBuilder>(".dynstr");
        strtab->AddString("func1");

        // Add a segment covering the section
        auto segment = std::make_unique<Builder::Components::LoadSegmentBuilder>();
        segment->AddSection(strtab.get());
        segment->SetFlags(4); // R
        builder.AddSegment(std::move(segment));

        builder.AddSection(std::move(strtab));

        Common::Result res = builder.Build();
        ASSERT_TRUE(res.IsOk());
    }

    // 2. Verify
    {
        IO::BinaryReader reader(testFile);
        bool open = reader.Open();
        ASSERT_TRUE(open);

        Model::Elf64_Ehdr header;
        bool read = reader.Read(header);
        ASSERT_TRUE(read);

        // Verify Magic
        ASSERT_TRUE(header.e_ident[Model::EI_MAG0] == 0x7f);
        ASSERT_TRUE(header.e_ident[Model::EI_MAG1] == 'E');
        ASSERT_TRUE(header.e_ident[Model::EI_MAG2] == 'L');
        ASSERT_TRUE(header.e_ident[Model::EI_MAG3] == 'F');

        // Verify Fields
        ASSERT_TRUE(header.e_type == static_cast<uint16_t>(Model::ElfType::Exec));
        ASSERT_TRUE(header.e_machine == static_cast<uint16_t>(Model::ElfMachine::X86_64));
        ASSERT_TRUE(header.e_entry == 0x400000);

        // Verify Section Headers count
        // Null section + .shstrtab + .dynstr = 3
        ASSERT_TRUE(header.e_shnum == 3);
    }

    // Cleanup
    std::remove(testFile.c_str());
}
