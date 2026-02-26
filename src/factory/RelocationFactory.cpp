#include "elfparser/factory/RelocationFactory.h"
#include "elfparser/model/impl/RelocationImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::IRelocation> RelocationFactory::CreateRelocation(const Model::Elf64_Rela& rela) {
        return std::make_unique<Model::Impl::RelocationImpl>(rela);
    }

}
