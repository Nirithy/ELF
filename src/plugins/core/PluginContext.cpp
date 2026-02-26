#include "elfparser/plugins/core/PluginContext.h"
#include "elfparser/plugins/events/EventDispatcher.h"

namespace ElfParser::Plugins {

    PluginContext::PluginContext(std::shared_ptr<Events::EventDispatcher> dispatcher)
        : m_dispatcher(std::move(dispatcher))
    {
    }

    PluginContext::~PluginContext() = default;

    Events::EventDispatcher& PluginContext::GetEventDispatcher() const {
        return *m_dispatcher;
    }

    API::ISymbolAPI* PluginContext::GetSymbolAPI() const {
        return nullptr;
    }

    API::ISectionAPI* PluginContext::GetSectionAPI() const {
        return nullptr;
    }

    API::ISegmentAPI* PluginContext::GetSegmentAPI() const {
        return nullptr;
    }

    API::IRelocationAPI* PluginContext::GetRelocationAPI() const {
        return nullptr;
    }

    API::IDynamicAPI* PluginContext::GetDynamicAPI() const {
        return nullptr;
    }

    API::INoteAPI* PluginContext::GetNoteAPI() const {
        return nullptr;
    }

    API::IVersionAPI* PluginContext::GetVersionAPI() const {
        return nullptr;
    }

}
