#pragma once

#include "elfparser/transform/ITransformation.h"
#include <string>

namespace ElfParser::Transform::Actions {

    class RemoveSectionAction : public ITransformation {
    public:
        explicit RemoveSectionAction(const std::string& sectionName);
        Common::Result Apply(Builder::ElfBuilder& builder) override;

    private:
        std::string m_sectionName;
    };

}
