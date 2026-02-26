#pragma once

#include "elfparser/transform/ITransformation.h"

namespace ElfParser::Transform::Actions {

    class StripSymbolsAction : public ITransformation {
    public:
        Common::Result Apply(Builder::ElfBuilder& builder) override;
    };

}
