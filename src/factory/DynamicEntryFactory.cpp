#include "elfparser/factory/DynamicEntryFactory.h"
#include "elfparser/model/impl/DynamicEntryImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::IDynamicEntry> DynamicEntryFactory::CreateDynamicEntry(const Model::Elf64_Dyn& dyn) {
        return std::make_unique<Model::Impl::DynamicEntryImpl>(dyn);
    }

}
