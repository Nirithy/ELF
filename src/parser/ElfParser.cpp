#include "elfparser/parser/ElfParser.h"
#include "elfparser/parser/components/HeaderParser.h"
#include "elfparser/parser/components/SectionParser.h"
#include "elfparser/parser/components/SegmentParser.h"
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
        Components::HeaderParser headerParser;
        auto res = headerParser.Parse(*m_reader, m_header);
        if (!res.IsOk()) return res;

        // 2. Parse Program Headers
        Components::SegmentParser segmentParser;
        res = segmentParser.ParseHeaders(*m_reader, m_header, m_phdrs);
        if (!res.IsOk()) return res;

        // 3. Parse Section Headers
        Components::SectionParser sectionParser;
        res = sectionParser.ParseHeaders(*m_reader, m_header, m_shdrs);
        if (!res.IsOk()) return res;

        // 4. Parse Section Names
        res = sectionParser.ParseStringTable(*m_reader, m_header, m_shdrs, m_shstrtab);
        if (!res.IsOk()) return res;

        Utils::Logger::Info("Successfully parsed ELF file.");
        return Common::Result::Ok();
    }

    std::string ElfParser::GetSectionName(uint32_t offset) const {
        return Components::SectionParser::GetSectionName(m_shstrtab, offset);
    }

}
