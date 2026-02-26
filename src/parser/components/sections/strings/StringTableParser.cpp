#include "elfparser/parser/components/sections/strings/StringTableParser.h"
#include "elfparser/utils/Logger.h"

namespace ElfParser::Parser::Components {

    Common::Result StringTableParser::Parse(IO::BinaryReader& reader,
                                            const Model::Elf64_Shdr& shdr,
                                            std::vector<char>& tableData) {

        if (!reader.Seek(shdr.sh_offset)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to string table section");
        }

        tableData.resize(shdr.sh_size);
        if (!reader.Read(tableData.data(), shdr.sh_size)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read string table data");
        }

        return Common::Result::Ok();
    }

    std::string StringTableParser::GetString(const std::vector<char>& tableData, uint32_t offset) {
        if (offset >= tableData.size()) {
            return "<invalid_offset>";
        }

        const char* start = tableData.data() + offset;
        const char* end = tableData.data() + tableData.size();

        for (const char* p = start; p < end; ++p) {
            if (*p == '\0') {
                return std::string(start);
            }
        }

        return "<unterminated_string>";
    }

}
