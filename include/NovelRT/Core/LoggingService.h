// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_LOGGINGSERVICE_H
#define NOVELRT_LOGGINGSERVICE_H

namespace NovelRT::Core
{
    enum class LogLevel
    {
        Debug = SPDLOG_LEVEL_DEBUG,
        Info = SPDLOG_LEVEL_INFO,
        Warn = SPDLOG_LEVEL_WARN,
        Err = SPDLOG_LEVEL_ERROR,
        Off = SPDLOG_LEVEL_OFF
    };
    class LoggingService
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
        static inline const char* CONSOLE_LOG_GENERIC = "NovelRT";
        static inline const char* CONSOLE_LOG_APP = "Application";
        static inline const char* CONSOLE_LOG_DOTNET = ".NET";
        static inline const char* CONSOLE_LOG_GFX = "GFX";
        static inline const char* CONSOLE_LOG_STATS = "Statistics";
        static inline const char* CONSOLE_LOG_AUDIO = "Audio";
        static inline const char* CONSOLE_LOG_INPUT = "Input";
        static inline const char* CONSOLE_LOG_WINDOWING = "WindowManager";

        LoggingService() noexcept;
        LoggingService(const std::string& core) noexcept;
        LoggingService(const std::string& core, LogLevel level) noexcept;
        void log(const std::string& message, LogLevel level);
        void logInfoLine(const std::string& message) const;
        void logErrorLine(const std::string& message) const;
        void logWarningLine(const std::string& message) const;
        void logDebugLine(const std::string& message) const;
        void logInternal(const std::string& message, LogLevel level);
        void setLogLevel(LogLevel level);
        void throwIfNullPtr(const void* const object, const std::string& exceptionMessage);
        void throwIfNotZero(int32_t error, const std::string& exceptionMessage);

        template<typename I, typename... IRest> void logInfo(I current, IRest... next) const
        {
            _logger->info(fmt::runtime(current), std::forward<IRest>(next)...);
        }
        template<typename E, typename... ERest> void logError(E current, ERest... next) const
        {
            _logger->error(fmt::runtime(current), std::forward<ERest>(next)...);
        }
        template<typename W, typename... WRest> void logWarning(W current, WRest... next) const
        {
            _logger->warn(fmt::runtime(current), std::forward<WRest>(next)...);
        }
        template<typename D, typename... DRest> void logDebug(D current, DRest... next) const
        {
            _logger->debug(fmt::runtime(current), std::forward<DRest>(next)...);
        }
    };

}

#endif
