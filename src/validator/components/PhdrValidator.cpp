#include "elfparser/validator/components/PhdrValidator.h"
#include "elfparser/model/enums/ElfSegmentType.h"

namespace ElfParser::Validator::Components {

    Common::Result PhdrValidator::Validate(const Model::Elf64_Phdr& header) {
        // Alignment check for LOAD segments
        // p_vaddr and p_offset must be congruent modulo p_align.
        if (header.p_type == static_cast<uint32_t>(Model::ElfSegmentType::Load)) {
            if (header.p_align > 1) {
                if ((header.p_vaddr % header.p_align) != (header.p_offset % header.p_align)) {
                    return Common::Result{Common::StatusCode::InvalidFormat,
                        "PT_LOAD: p_vaddr and p_offset are not congruent modulo p_align"};
                }
            }
        }
        return Common::Result::Ok();
    }

}
