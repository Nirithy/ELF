#pragma once

namespace ElfParser::Interface {

    class ISection;
    class ISegment;
    class ISymbol;
    class IRelocation;
    class IDynamicEntry;
    class INode;

    /**
     * @brief Interface for the Visitor pattern.
     * Allows operations to be performed on ELF elements without modifying their classes.
     */
    class IVisitor {
    public:
        virtual ~IVisitor() = default;

        virtual void Visit(ISection& section) = 0;
        virtual void Visit(ISegment& segment) = 0;
        virtual void Visit(ISymbol& symbol) = 0;
        virtual void Visit(IRelocation& relocation) = 0;
        virtual void Visit(IDynamicEntry& dynamicEntry) = 0;

        // Fallback or generic visit if needed
        virtual void Visit(INode& node) = 0;
    };

}
