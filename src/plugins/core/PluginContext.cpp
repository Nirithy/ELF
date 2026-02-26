#include "elfparser/plugins/core/PluginContext.h"
#include "elfparser/plugins/events/EventDispatcher.h"

namespace ElfParser::Plugins {

    PluginContext::PluginContext(std::shared_ptr<Events::EventDispatcher> dispatcher)
        : m_dispatcher(std::move(dispatcher)) {}

    PluginContext::~PluginContext() = default;

    Events::EventDispatcher& PluginContext::GetEventDispatcher() const {
        return *m_dispatcher;
    }

}
