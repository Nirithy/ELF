#pragma once

#include <memory>

namespace ElfParser::Plugins {

    namespace Events {
        class EventDispatcher;
    }

    /**
     * @brief Context passed to plugins during initialization.
     * Provides access to core system services.
     */
    class PluginContext {
    public:
        explicit PluginContext(std::shared_ptr<Events::EventDispatcher> dispatcher);
        ~PluginContext();

        Events::EventDispatcher& GetEventDispatcher() const;

    private:
        std::shared_ptr<Events::EventDispatcher> m_dispatcher;
    };

}
