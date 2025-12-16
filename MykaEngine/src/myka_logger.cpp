#include "myka_logger.hpp"

namespace MykaEngine
{
    void Logger::log(LogLevel level, const std::string &message)
    {
        using enum LogLevel;

        switch (level)
        {
        case Debug:
            logDebug(message);
            break;

        case Info:
            logInfo(message);
            break;

        case Warning:
            logWarning(message);
            break;

        case Error:
            logError(message);
            break;

        case Fatal:
            logFatal(message);
            break;

        default:
            logError("wrong log level");
        }
    }

    void Logger::logDebug(const std::string &message)
    {
        std::cout << "DEBUG: " << message << std::endl;
    }

    void Logger::logInfo(const std::string &message)
    {
        std::cout << "INFO: " << message << std::endl;
    }

    void Logger::logWarning(const std::string &message)
    {
        std::cerr << "WARNING: " << message << std::endl;
    }

    void Logger::logError(const std::string &message)
    {
        std::cerr << "ERROR: " << message << std::endl;
    }

    void Logger::logFatal(const std::string &message)
    {
        throw std::runtime_error("FATAL: " + message);
    }
} // namespace MykaEngine
