#include "elfparser/factory/SectionFactory.h"
#include "elfparser/model/impl/SectionImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::ISection> SectionFactory::CreateSection(
        const std::string& name,
        Model::ElfSectionType type
    ) {
        return std::make_unique<Model::SectionImpl>(name, type);
    }

}
