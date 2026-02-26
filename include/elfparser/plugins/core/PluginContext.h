#pragma once

#include <memory>

namespace ElfParser::Plugins {

    namespace Events {
        class EventDispatcher;
    }

    namespace API {
        class ISymbolAPI;
        class ISectionAPI;
        class ISegmentAPI;
        class IRelocationAPI;
        class IDynamicAPI;
        class INoteAPI;
        class IVersionAPI;
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

        API::ISymbolAPI* GetSymbolAPI() const;
        API::ISectionAPI* GetSectionAPI() const;
        API::ISegmentAPI* GetSegmentAPI() const;
        API::IRelocationAPI* GetRelocationAPI() const;
        API::IDynamicAPI* GetDynamicAPI() const;
        API::INoteAPI* GetNoteAPI() const;
        API::IVersionAPI* GetVersionAPI() const;

    private:
        std::shared_ptr<Events::EventDispatcher> m_dispatcher;
    };

}
