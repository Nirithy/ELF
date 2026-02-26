#pragma once

#include <cstdint>

namespace ElfParser::Plugins::Events {

    enum class EventType : uint32_t {
        Unknown = 0,

        // Lifecycle events
        PluginLoaded,
        PluginUnloaded,

        // Parse events
        ParseStart,
        ParseEnd,
        SectionParsed,
        SymbolTableParsed,

        // Build events
        BuildStart,
        BuildEnd,
        LayoutCalculated,

        // Error events
        ErrorOccurred,

        // Custom events for plugins
        Custom = 1000
    };

}
