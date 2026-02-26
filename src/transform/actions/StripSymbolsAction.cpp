#include "elfparser/transform/actions/StripSymbolsAction.h"

namespace ElfParser::Transform::Actions {

    Common::Result StripSymbolsAction::Apply(Builder::ElfBuilder& builder) {
        // Remove symbol table and associated string table
        builder.RemoveSection(".symtab");
        builder.RemoveSection(".strtab");
        return Common::Result::Ok();
    }

}
