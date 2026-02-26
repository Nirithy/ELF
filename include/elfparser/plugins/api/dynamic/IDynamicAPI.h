#pragma once

#include "elfparser/common/Types.h"
#include <vector>
#include <string>

namespace ElfParser::Interface {
    class IDynamicEntry;
}

namespace ElfParser::Plugins::API {

    /**
     * @brief API for interacting with ELF Dynamic Section.
     */
    class IDynamicAPI {
    public:
        virtual ~IDynamicAPI() = default;

        /**
         * @brief Get all dynamic entries.
         */
        virtual std::vector<Interface::IDynamicEntry*> GetDynamicEntries() = 0;

        /**
         * @brief Add a dynamic entry.
         */
        virtual Interface::IDynamicEntry* AddDynamicEntry(int64_t tag, uint64_t value) = 0;

        /**
         * @brief Remove dynamic entries with a specific tag.
         */
        virtual Common::Result RemoveDynamicEntry(int64_t tag) = 0;
    };

}
