// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

module;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275)
#endif

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <iostream>

module NovelRT.Logging:LoggingService;
import NovelRT.Exceptions;

#ifndef NDEBUG
typedef spdlog::synchronous_factory spdlog_factory;
#else
typedef spdlog::async_factory spdlog_factory;
#endif

namespace NovelRT::Logging
{
    export enum class LogLevel
    {
        Debug = SPDLOG_LEVEL_DEBUG,
        Info = SPDLOG_LEVEL_INFO,
        Warn = SPDLOG_LEVEL_WARN,
        Err = SPDLOG_LEVEL_ERROR,
        Off = SPDLOG_LEVEL_OFF
    };

    export class LoggingService
    {
    private:
        std::shared_ptr<spdlog::logger> _logger;
        inline void logDebug()
        {
        }
        inline void logWarning()
        {
        }
        inline void logError()
        {
        }
        inline void logInfo()
        {
        }

    public:
        LoggingService() noexcept
        {
            try
            {
                _logger = spdlog::get("GENERIC");
                if (_logger == nullptr)
                {
                    _logger = spdlog::stdout_color_mt<spdlog_factory>("GENERIC");
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

        LoggingService(const std::string& core) noexcept
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

        LoggingService(const std::string& core, LogLevel level) noexcept
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

        void log(const std::string& message, LogLevel level) const
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

        void logInfoLine(const std::string& message) const
        {
            _logger->info(message);
        }

        void logErrorLine(const std::string& message) const
        {
            _logger->error(message);
        }

        void logWarningLine(const std::string& message) const
        {
            _logger->warn(message);
        }

        void logDebugLine(const std::string& message) const
        {
            _logger->debug(message);
        }

        void logInternal(const std::string& message, LogLevel level)
        {
            log(message, level);
        }

        void setLogLevel(LogLevel level)
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

        void throwIfNullPtr(const void* const object, const std::string& exceptionMessage)
        {
            if (object != nullptr)
                return;
            logError(exceptionMessage);
            throw Exceptions::NullPointerException(exceptionMessage);
        }

        void throwIfNotZero(int32_t error, const std::string& exceptionMessage)
        {
            if (error == 0)
                return;
            logError(exceptionMessage);
            throw std::runtime_error(exceptionMessage);
        }


        template<typename I, typename... IRest>
        void logInfo(I current, IRest... next) const
        {
            _logger->info(fmt::runtime(current), std::forward<IRest>(next)...);
        }
        template<typename E, typename... ERest>
        void logError(E current, ERest... next) const
        {
            _logger->error(fmt::runtime(current), std::forward<ERest>(next)...);
        }
        template<typename W, typename... WRest>
        void logWarning(W current, WRest... next) const
        {
            _logger->warn(fmt::runtime(current), std::forward<WRest>(next)...);
        }
        template<typename D, typename... DRest>
        void logDebug(D current, DRest... next) const
        {
            _logger->debug(fmt::runtime(current), std::forward<DRest>(next)...);
        }
    };

}
