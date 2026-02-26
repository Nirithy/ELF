#pragma once

#include <string>
#include <vector>

namespace ElfParser::Plugins {

    /**
     * @brief Metadata about a plugin.
     */
    struct PluginInfo {
        std::string name;
        std::string version;
        std::string description;
        std::string author;
        std::vector<std::string> dependencies;
    };

}
