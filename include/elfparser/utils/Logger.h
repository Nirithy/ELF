#pragma once

#include <string>
#include <mutex>

namespace ElfParser::Utils {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    class Logger {
    public:
        static Logger& Get();

        // Delete copy/move
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        void SetLevel(LogLevel level);
        void Log(LogLevel level, const std::string& message);

        // Helper methods
        static void Debug(const std::string& msg);
        static void Info(const std::string& msg);
        static void Warn(const std::string& msg);
        static void Error(const std::string& msg);

    private:
        Logger();
        ~Logger();

        std::mutex m_mutex;
        LogLevel m_minLevel;
    };

}
