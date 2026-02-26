#include "elfparser/validator/components/ShdrValidator.h"
#include "elfparser/model/enums/ElfSectionType.h"

namespace ElfParser::Validator::Components {

    Common::Result ShdrValidator::Validate(const Model::Elf64_Shdr& header) {
        // Basic overflow check
        if (header.sh_offset + header.sh_size < header.sh_offset) {
            return Common::Result{Common::StatusCode::InvalidFormat, "Section size causes overflow"};
        }

        // Validate SHT_SYMTAB entry size
        if (header.sh_type == static_cast<uint32_t>(Model::ElfSectionType::Symtab)) {
             // Elf64_Sym is 24 bytes
             if (header.sh_entsize < 24) {
                 return Common::Result{Common::StatusCode::InvalidFormat, "Invalid SHT_SYMTAB entry size"};
             }
        }

        return Common::Result::Ok();
    }

}
