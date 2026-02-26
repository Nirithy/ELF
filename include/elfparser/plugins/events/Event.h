#pragma once

#include "elfparser/plugins/events/EventTypes.h"
#include <string>

namespace ElfParser::Plugins::Events {

    class Event {
    public:
        explicit Event(EventType type, const std::string& message = "")
            : m_type(type), m_message(message) {}

        virtual ~Event() = default;

        EventType GetType() const { return m_type; }
        const std::string& GetMessage() const { return m_message; }

    private:
        EventType m_type;
        std::string m_message;
    };

}
