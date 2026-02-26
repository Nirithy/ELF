#include "elfparser/plugins/loaders/StaticPluginLoader.h"
#include "elfparser/plugins/registry/PluginRegistry.h"
// Include static plugins headers here if any (currently none to include)

namespace ElfParser::Plugins::Loaders {

    Common::Result StaticPluginLoader::Load() {
        // In a real scenario, this would register known static plugins.
        // For now, it's a placeholder.
        // Example:
        // auto plugin = std::make_shared<MyStaticPlugin>();
        // Registry::PluginRegistry::GetInstance().RegisterPlugin(plugin);

        return Common::Result::Ok();
    }

}
