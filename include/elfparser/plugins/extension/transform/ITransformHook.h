#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Interface {
    class ISection;
}

namespace ElfParser::Plugins::Extensions {

    class ITransformHook : public IExtension {
    public:
        virtual ~ITransformHook() = default;

        virtual Common::Result TransformSection(Interface::ISection* section) = 0;
    };
}
