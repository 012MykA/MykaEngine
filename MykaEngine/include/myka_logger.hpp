#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

namespace MykaEngine
{
    enum class LogLevel
    {
        Debug = 0, Info, Warning, Error, Fatal
    };

    class Logger
    {
    public:
        static void log(LogLevel level, const std::string& message);

        static void logDebug(const std::string& message);
        static void logInfo(const std::string& message);
        static void logWarning(const std::string& message);
        static void logError(const std::string& message);
        static void logFatal(const std::string& message);

    private:
    };
} // namespace MykaEngine
