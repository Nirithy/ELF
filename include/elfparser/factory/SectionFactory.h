#pragma once

#include <memory>
#include <string>
#include "elfparser/interface/ISection.h"
#include "elfparser/model/enums/ElfSectionType.h"

namespace ElfParser::Factory {

    class SectionFactory {
    public:
        /**
         * @brief Creates a new Section instance.
         * @param name The name of the section.
         * @param type The type of the section.
         * @return A unique pointer to the created section.
         */
        static std::unique_ptr<Interface::ISection> CreateSection(
            const std::string& name,
            Model::ElfSectionType type = Model::ElfSectionType::Null
        );
    };

}
