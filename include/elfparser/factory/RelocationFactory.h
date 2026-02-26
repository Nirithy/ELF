#pragma once

#include <memory>
#include "elfparser/interface/IRelocation.h"
#include "elfparser/model/ElfStructures.h"

namespace ElfParser::Factory {

    class RelocationFactory {
    public:
        /**
         * @brief Creates a new Relocation instance.
         * @param rela The raw relocation structure.
         * @return A unique pointer to the created relocation.
         */
        static std::unique_ptr<Interface::IRelocation> CreateRelocation(const Model::Elf64_Rela& rela);
    };

}
