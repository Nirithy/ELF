#pragma once

#include "elfparser/interface/IVisitor.h"
#include "elfparser/interface/INode.h"
#include "elfparser/interface/ISection.h"
#include "elfparser/interface/ISegment.h"
#include "elfparser/interface/ISymbol.h"
#include "elfparser/interface/IRelocation.h"
#include "elfparser/interface/IDynamicEntry.h"

namespace ElfParser::Visitor {

    /**
     * @brief A default implementation of IVisitor that does nothing.
     * Useful as a base class for visitors that only care about specific elements.
     */
    class BaseVisitor : public Interface::IVisitor {
    public:
        ~BaseVisitor() override = default;

        void Visit(Interface::ISection& section) override {}
        void Visit(Interface::ISegment& segment) override {}
        void Visit(Interface::ISymbol& symbol) override {}
        void Visit(Interface::IRelocation& relocation) override {}
        void Visit(Interface::IDynamicEntry& dynamicEntry) override {}
        void Visit(Interface::INode& node) override {}
    };

}
