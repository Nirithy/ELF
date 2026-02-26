#include "elfparser/plugins/events/EventDispatcher.h"

namespace ElfParser::Plugins::Events {

    void EventDispatcher::RegisterListener(std::shared_ptr<IEventListener> listener) {
        if (!listener) return;
        std::lock_guard<std::mutex> lock(m_mutex);

        // Avoid duplicates
        auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
        if (it == m_listeners.end()) {
            m_listeners.push_back(listener);
        }
    }

    void EventDispatcher::UnregisterListener(std::shared_ptr<IEventListener> listener) {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
        if (it != m_listeners.end()) {
            m_listeners.erase(it);
        }
    }

    void EventDispatcher::Dispatch(const Event& event) {
        std::lock_guard<std::mutex> lock(m_mutex);
        // Copy listeners to avoid issues if listeners modify the list during callback
        auto listeners = m_listeners;
        for (const auto& listener : listeners) {
            listener->OnEvent(event);
        }
    }

}
