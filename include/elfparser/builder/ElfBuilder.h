#pragma once

#include <string>
#include <vector>
#include <memory>
#include "elfparser/builder/components/headers/EhdrBuilder.h"
#include "elfparser/builder/components/headers/PhdrBuilder.h"
#include "elfparser/builder/components/headers/ShdrBuilder.h"
#include "elfparser/builder/components/sections/SectionBuilder.h"
#include "elfparser/builder/components/sections/StringTableBuilder.h"
#include "elfparser/io/BinaryWriter.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Builder {

    class ElfBuilder {
    public:
        explicit ElfBuilder(const std::string& outputPath);

        // Accessors
        Components::EhdrBuilder& GetHeaderBuilder();
        Components::PhdrBuilder& GetProgramHeaderBuilder();
        Components::ShdrBuilder& GetSectionHeaderBuilder();

        // Add a section (takes ownership)
        void AddSection(std::unique_ptr<Components::SectionBuilder> section);

        // Get the internal section header string table builder
        Components::StringTableBuilder& GetSectionHeaderStringTable();

        // Compute layout and write to file
        Common::Result Build();

    private:
        std::string m_outputPath;
        Components::EhdrBuilder m_ehdrBuilder;
        Components::PhdrBuilder m_phdrBuilder;
        Components::ShdrBuilder m_shdrBuilder;

        // Sections
        std::vector<std::unique_ptr<Components::SectionBuilder>> m_sections;

        // Raw pointer to the .shstrtab section (owned by m_sections)
        Components::StringTableBuilder* m_shstrtabRef = nullptr;
    };

}
