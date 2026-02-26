#include "elfparser/parser/components/headers/PhdrParser.h"
#include "elfparser/utils/ElfSwap.h"
#include <string>

namespace ElfParser::Parser::Components {

    Common::Result PhdrParser::ParseHeaders(IO::BinaryReader& reader, const Model::Elf64_Ehdr& header, std::vector<Model::Elf64_Phdr>& segments) {
        if (header.e_phoff == 0 || header.e_phnum == 0) {
            segments.clear();
            return Common::Result::Ok();
        }

        if (!reader.Seek(header.e_phoff)) {
            return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to seek to Program Headers");
        }

        segments.resize(header.e_phnum);
        for (int i = 0; i < header.e_phnum; ++i) {
            if (!reader.Read(segments[i])) {
                return Common::Result::Fail(Common::StatusCode::ReadError, "Failed to read Program Header " + std::to_string(i));
            }
            if (reader.ShouldSwap()) {
                Utils::Swap(segments[i]);
            }
        }
        return Common::Result::Ok();
    }

}
