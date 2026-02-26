#pragma once

#include "elfparser/plugins/extension/IExtension.h"
#include "elfparser/common/Types.h"

namespace ElfParser::Interface {
    class IEhdr;
    class ISection;
}

namespace ElfParser::Plugins::Extensions {

    class IParserHook : public IExtension {
    public:
        virtual ~IParserHook() = default;

        virtual void OnHeaderParsed(const Interface::IEhdr* ehdr) = 0;
        virtual void OnSectionParsed(const Interface::ISection* section) = 0;
    };
}
