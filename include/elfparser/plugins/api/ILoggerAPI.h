#pragma once

#include <string>

namespace ElfParser::Plugins::API {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    /**
     * @brief Interface for logging from plugins.
     */
    class ILoggerAPI {
    public:
        virtual ~ILoggerAPI() = default;

        /**
         * @brief Log a message.
         * @param level The severity level.
         * @param message The message to log.
         */
        virtual void Log(LogLevel level, const std::string& message) = 0;

        /**
         * @brief Log an info message.
         * @param message The message to log.
         */
        virtual void Info(const std::string& message) {
            Log(LogLevel::Info, message);
        }

        /**
         * @brief Log a warning message.
         * @param message The message to log.
         */
        virtual void Warning(const std::string& message) {
            Log(LogLevel::Warning, message);
        }

        /**
         * @brief Log an error message.
         * @param message The message to log.
         */
        virtual void Error(const std::string& message) {
            Log(LogLevel::Error, message);
        }
    };

}
