#include "elfparser/factory/VersionFactory.h"
#include "elfparser/model/impl/VersionDefinitionImpl.h"
#include "elfparser/model/impl/VersionRequirementImpl.h"

namespace ElfParser::Factory {

    std::unique_ptr<Interface::IVersionDefinition> VersionFactory::CreateVersionDefinition() {
        return std::make_unique<Model::Impl::VersionDefinitionImpl>();
    }

    std::unique_ptr<Interface::IVersionRequirement> VersionFactory::CreateVersionRequirement() {
        return std::make_unique<Model::Impl::VersionRequirementImpl>();
    }

}
