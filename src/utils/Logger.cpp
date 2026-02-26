#include "elfparser/utils/Logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace ElfParser::Utils {

    Logger& Logger::Get() {
        static Logger instance;
        return instance;
    }

    Logger::Logger() : m_minLevel(LogLevel::Info) {}
    Logger::~Logger() = default;

    void Logger::SetLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_minLevel = level;
    }

    void Logger::Log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (level < m_minLevel) return;

        // Get current time
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);

        const char* levelStr = "[UNK]";
        switch (level) {
            case LogLevel::Debug: levelStr = "[DBG]"; break;
            case LogLevel::Info:  levelStr = "[INF]"; break;
            case LogLevel::Warning: levelStr = "[WRN]"; break;
            case LogLevel::Error: levelStr = "[ERR]"; break;
        }

        // Standard C++ doesn't guarantee thread-safety for localtime,
        // but the mutex here protects concurrent calls within this class.
        std::tm* tm_ptr = std::localtime(&time_t);

        if (tm_ptr) {
             std::clog << "[" << std::put_time(tm_ptr, "%H:%M:%S") << "] "
                  << levelStr << " " << message << std::endl;
        } else {
             std::clog << "[TIME_ERR] " << levelStr << " " << message << std::endl;
        }
    }

    void Logger::Debug(const std::string& msg) { Get().Log(LogLevel::Debug, msg); }
    void Logger::Info(const std::string& msg) { Get().Log(LogLevel::Info, msg); }
    void Logger::Warn(const std::string& msg) { Get().Log(LogLevel::Warning, msg); }
    void Logger::Error(const std::string& msg) { Get().Log(LogLevel::Error, msg); }

}
