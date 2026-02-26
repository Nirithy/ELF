#include "elfparser/transform/actions/RemoveSectionAction.h"

namespace ElfParser::Transform::Actions {

    RemoveSectionAction::RemoveSectionAction(const std::string& sectionName)
        : m_sectionName(sectionName) {}

    Common::Result RemoveSectionAction::Apply(Builder::ElfBuilder& builder) {
        builder.RemoveSection(m_sectionName);
        return Common::Result::Ok();
    }

}
