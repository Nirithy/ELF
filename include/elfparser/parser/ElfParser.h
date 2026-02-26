#pragma once

#include <string>
#include <memory>
#include <vector>
#include "elfparser/common/Types.h"
#include "elfparser/model/ElfStructures.h"
#include "elfparser/io/BinaryReader.h"

namespace ElfParser::Parser {

    class ElfParser {
    public:
        explicit ElfParser(const std::string& filepath);
        ~ElfParser();

        // Parse the ELF file. Returns success or failure.
        Common::Result Parse();

        // Accessors
        const Model::Elf64_Ehdr& GetHeader() const { return m_header; }
        const std::vector<Model::Elf64_Phdr>& GetProgramHeaders() const { return m_phdrs; }
        const std::vector<Model::Elf64_Shdr>& GetSectionHeaders() const { return m_shdrs; }

        const std::vector<Model::Elf64_Sym>& GetSymbols() const { return m_symbols; }
        const std::vector<Model::Elf64_Dyn>& GetDynamicEntries() const { return m_dynamicEntries; }
        const std::vector<Model::Elf64_Rela>& GetRelocations() const { return m_relocations; }

        // Helper to get section name from the Section Header String Table
        std::string GetSectionName(uint32_t offset) const;

    private:
        std::string m_filepath;
        std::unique_ptr<IO::BinaryReader> m_reader;

        Model::Elf64_Ehdr m_header;
        std::vector<Model::Elf64_Phdr> m_phdrs;
        std::vector<Model::Elf64_Shdr> m_shdrs;

        // Section header string table raw data
        std::vector<char> m_shstrtab;

        // Parsed data
        std::vector<Model::Elf64_Sym> m_symbols;
        std::vector<Model::Elf64_Dyn> m_dynamicEntries;
        std::vector<Model::Elf64_Rela> m_relocations;
    };

}
