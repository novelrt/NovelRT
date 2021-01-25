// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <iostream>

namespace NovelRT
{

#ifndef NDEBUG
    typedef spdlog::synchronous_factory spdlog_factory;
#else
    typedef spdlog::async_factory spdlog_factory;
#endif

    LoggingService::LoggingService()
    {
        try
        {
            _logger = spdlog::get(Utilities::Misc::CONSOLE_LOG_GENERIC);
            if (_logger == nullptr)
            {
                _logger = spdlog::stdout_color_mt<spdlog_factory>(Utilities::Misc::CONSOLE_LOG_GENERIC);
            }

#ifndef NDEBUG
            setLogLevel(LogLevel::Debug);
#else
            setLogLevel(LogLevel::Info);
#endif

            // Set spdlog's error handler in case it fails.
            spdlog::set_error_handler(
                [](const std::string& msg) { std::cerr << "SPDLOG ERROR: " << msg << std::endl; });
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
        }
    }

    LoggingService::LoggingService(const std::string& core)
    {
        try
        {
            _logger = spdlog::get(core);
            if (_logger == nullptr)
            {
                _logger = spdlog::stdout_color_mt<spdlog_factory>(core);
            }

#ifndef NDEBUG
            setLogLevel(LogLevel::Debug);
#else
            setLogLevel(LogLevel::Info);
#endif

            // Set spdlog's error handler in case it fails.
            spdlog::set_error_handler(
                [](const std::string& msg) { std::cerr << "SPDLOG ERROR: " << msg << std::endl; });
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
        }
    }

    LoggingService::LoggingService(const std::string& core, LogLevel level)
    {
        try
        {
            _logger = spdlog::get(core);
            if (_logger == nullptr)
            {
                _logger = spdlog::stdout_color_mt<spdlog_factory>(core);
            }

            setLogLevel(level);

            // Set spdlog's error handler in case it fails.
            spdlog::set_error_handler(
                [](const std::string& msg) { std::cerr << "SPDLOG ERROR: " << msg << std::endl; });
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
        }
    }

    void LoggingService::log(const std::string& message, LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Debug:
                _logger->debug(message);
                break;
            case LogLevel::Info:
                _logger->info(message);
                break;
            case LogLevel::Warn:
                _logger->warn(message);
                break;
            case LogLevel::Err:
                _logger->error(message);
                break;
            case LogLevel::Off:
                break;
        }
    }

    void LoggingService::logInfoLine(const std::string& message)
    {
        _logger->info(message);
    }

    void LoggingService::logErrorLine(const std::string& message)
    {
        _logger->error(message);
    }

    void LoggingService::logWarningLine(const std::string& message)
    {
        _logger->warn(message);
    }

    void LoggingService::logDebugLine(const std::string& message)
    {
        _logger->debug(message);
    }

    void LoggingService::logInternal(const std::string& message, LogLevel level)
    {
#ifndef NDEBUG
        log(message, level);
#else
        unused(message);
        unused(level);
#endif
    }

    void LoggingService::setLogLevel(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Debug:
                _logger->set_level(spdlog::level::level_enum::debug);
                break;
            case LogLevel::Info:
                _logger->set_level(spdlog::level::level_enum::info);
                break;
            case LogLevel::Warn:
                _logger->set_level(spdlog::level::level_enum::warn);
                break;
            case LogLevel::Err:
                _logger->set_level(spdlog::level::level_enum::err);
                break;
            case LogLevel::Off:
                _logger->set_level(spdlog::level::level_enum::off);
                break;
        }
    }

    void LoggingService::throwIfNullPtr(const void* const object, const std::string& exceptionMessage)
    {
        if (object != nullptr)
            return;
        logError(exceptionMessage);
        throw Exceptions::NullPointerException(exceptionMessage);
    }

    void LoggingService::throwIfNotZero(int32_t error, const std::string& exceptionMessage)
    {
        if (error == 0)
            return;
        logError(exceptionMessage);
        throw std::runtime_error(exceptionMessage);
    }
} // namespace NovelRT
