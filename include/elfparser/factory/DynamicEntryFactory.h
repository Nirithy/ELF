#pragma once

#include <memory>
#include "elfparser/interface/IDynamicEntry.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Factory {

    class DynamicEntryFactory {
    public:
        /**
         * @brief Creates a new Dynamic Entry instance.
         * @param dyn The raw dynamic entry structure.
         * @return A unique pointer to the created dynamic entry.
         */
        static std::unique_ptr<Interface::IDynamicEntry> CreateDynamicEntry(const Model::Elf64_Dyn& dyn);
    };

}
