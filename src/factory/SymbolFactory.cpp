#include "elfparser/factory/SymbolFactory.h"
#include "elfparser/model/impl/SymbolImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::ISymbol> SymbolFactory::CreateSymbol(const Model::Elf64_Sym& sym, const std::string& name) {
        return std::make_unique<Model::Impl::SymbolImpl>(sym, name);
    }

}
