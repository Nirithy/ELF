#pragma once

namespace ElfParser::Interface {

    class IVisitor;

    /**
     * @brief Base interface for all ELF components that can be visited.
     * Implements the Accept method of the Visitor pattern.
     */
    class INode {
    public:
        virtual ~INode() = default;

        /**
         * @brief Accepts a visitor.
         * @param visitor The visitor to accept.
         */
        virtual void Accept(IVisitor& visitor) = 0;
    };

}
