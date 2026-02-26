#include "elfparser/validator/components/EhdrValidator.h"
#include <cstring>

namespace ElfParser::Validator::Components {

    Common::Result EhdrValidator::Validate(const Model::Elf64_Ehdr& header) {
        // Check magic
        const unsigned char expectedMagic[] = { 0x7F, 'E', 'L', 'F' };
        if (std::memcmp(header.e_ident, expectedMagic, 4) != 0) {
            return Common::Result{Common::StatusCode::InvalidFormat, "Invalid ELF Magic"};
        }

        // Check version
        if (header.e_ident[Model::EI_VERSION] != 1) { // EV_CURRENT
             return Common::Result{Common::StatusCode::InvalidFormat, "Invalid ELF Version"};
        }

        return Common::Result::Ok();
    }

}
