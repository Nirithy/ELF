#pragma once

#include "elfparser/plugins/events/Event.h"
#include <memory>

namespace ElfParser::Plugins::Events {

    /**
     * @brief Interface for objects that listen for events.
     */
    class IEventListener {
    public:
        virtual ~IEventListener() = default;

        /**
         * @brief Called when an event is dispatched.
         * @param event The event object.
         */
        virtual void OnEvent(const Event& event) = 0;
    };

}
