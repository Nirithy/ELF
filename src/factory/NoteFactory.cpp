#include "elfparser/factory/NoteFactory.h"
#include "elfparser/model/impl/NoteImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::INote> NoteFactory::CreateNote(
        uint32_t type,
        const std::string& name,
        const std::vector<unsigned char>& descriptor
    ) {
        return std::make_unique<Model::Impl::NoteImpl>(type, name, descriptor);
    }

}
