#pragma once

#include <cstdint>
#include "elfparser/interface/INode.h"
#include "elfparser/model/enums/ElfDynamicTag.h"

namespace ElfParser::Interface {

    /**
     * @brief Interface for Dynamic Section Entries.
     */
    class IDynamicEntry : public INode {
    public:
        virtual ~IDynamicEntry() = default;

        virtual Model::ElfDynamicTag GetTag() const = 0;
        virtual void SetTag(Model::ElfDynamicTag tag) = 0;

        virtual uint64_t GetValue() const = 0;
        virtual void SetValue(uint64_t value) = 0;
    };

}
