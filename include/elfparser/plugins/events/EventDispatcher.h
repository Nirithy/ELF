#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>
#include "elfparser/plugins/events/IEventListener.h"

namespace ElfParser::Plugins::Events {

    /**
     * @brief Dispatches events to registered listeners.
     */
    class EventDispatcher {
    public:
        /**
         * @brief Register an event listener.
         * @param listener The listener to register.
         */
        void RegisterListener(std::shared_ptr<IEventListener> listener);

        /**
         * @brief Unregister an event listener.
         * @param listener The listener to unregister.
         */
        void UnregisterListener(std::shared_ptr<IEventListener> listener);

        /**
         * @brief Dispatch an event to all registered listeners.
         * @param event The event to dispatch.
         */
        void Dispatch(const Event& event);

    private:
        std::vector<std::shared_ptr<IEventListener>> m_listeners;
        mutable std::mutex m_mutex;
    };

}
