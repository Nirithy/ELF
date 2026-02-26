#include "elfparser/parser/ElfParser.h"
#include "elfparser/parser/components/headers/EhdrParser.h"
#include "elfparser/parser/components/headers/PhdrParser.h"
#include "elfparser/parser/components/headers/ShdrParser.h"
#include "elfparser/parser/components/sections/symbols/SymbolTableParser.h"
#include "elfparser/parser/components/sections/dynamic/DynamicSectionParser.h"
#include "elfparser/parser/components/sections/relocations/RelocationSectionParser.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser {

    ElfParser::ElfParser(const std::string& filepath)
        : m_filepath(filepath), m_reader(std::make_unique<IO::BinaryReader>(filepath)) {
    }

    ElfParser::~ElfParser() = default;

    Common::Result ElfParser::Parse() {
        if (!m_reader->Open()) {
            return Common::Result::Fail(Common::StatusCode::FileNotFound, "Could not open file: " + m_filepath);
        }

        Utils::Logger::Info("Parsing ELF file: " + m_filepath);

        // 1. Parse Header
        Components::EhdrParser ehdrParser;
        auto res = ehdrParser.Parse(*m_reader, m_header);
        if (!res.IsOk()) return res;

        // 2. Parse Program Headers
        Components::PhdrParser phdrParser;
        res = phdrParser.ParseHeaders(*m_reader, m_header, m_phdrs);
        if (!res.IsOk()) return res;

        // 3. Parse Section Headers
        Components::ShdrParser shdrParser;
        res = shdrParser.ParseHeaders(*m_reader, m_header, m_shdrs);
        if (!res.IsOk()) return res;

        // 4. Parse Section Names
        res = shdrParser.ParseStringTable(*m_reader, m_header, m_shdrs, m_shstrtab);
        if (!res.IsOk()) return res;

        // 5. Parse Other Sections
        for (const auto& section : m_shdrs) {
            if (section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Symtab) ||
                section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Dynsym)) {

                Components::SymbolTableParser symParser;
                std::vector<Model::Elf64_Sym> syms;
                auto res = symParser.Parse(*m_reader, m_header, section, syms);
                if (res.IsOk()) {
                    m_symbols.insert(m_symbols.end(), syms.begin(), syms.end());
                } else {
                    Utils::Logger::Error("Failed to parse symbol table: " + res.message);
                }
            }
            else if (section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Dynamic)) {
                Components::DynamicSectionParser dynParser;
                std::vector<Model::Elf64_Dyn> dyns;
                auto res = dynParser.Parse(*m_reader, m_header, section, dyns);
                if (res.IsOk()) {
                    m_dynamicEntries.insert(m_dynamicEntries.end(), dyns.begin(), dyns.end());
                } else {
                    Utils::Logger::Error("Failed to parse dynamic section: " + res.message);
                }
            }
            else if (section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Rel) ||
                     section.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Rela)) {
                Components::RelocationSectionParser relParser;
                std::vector<Model::Elf64_Rela> rels;
                auto res = relParser.Parse(*m_reader, m_header, section, rels);
                if (res.IsOk()) {
                    m_relocations.insert(m_relocations.end(), rels.begin(), rels.end());
                } else {
                    Utils::Logger::Error("Failed to parse relocations: " + res.message);
                }
            }
        }

        Utils::Logger::Info("Successfully parsed ELF file.");
        return Common::Result::Ok();
    }

    std::string ElfParser::GetSectionName(uint32_t offset) const {
        return Components::ShdrParser::GetSectionName(m_shstrtab, offset);
    }

}
