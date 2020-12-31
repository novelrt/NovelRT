// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_LOGGINGSERVICE_H
#define NOVELRT_LOGGINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT
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
        LoggingService();
        LoggingService(const std::string& core);
        LoggingService(const std::string& core, LogLevel level);
        void log(const std::string& message, LogLevel level);
        void logInfoLine(const std::string& message);
        void logErrorLine(const std::string& message);
        void logWarningLine(const std::string& message);
        void logDebugLine(const std::string& message);
        void logInternal(const std::string& message, LogLevel level);
        void setLogLevel(LogLevel level);
        void throwIfNullPtr(const void* const object, const std::string& exceptionMessage);
        void throwIfNotZero(int32_t error, const std::string& exceptionMessage);

        template <typename I, typename... IRest> void logInfo(I current, IRest... next)
        {
            _logger->info(current, std::forward<IRest>(next)...);
        }
        template <typename E, typename... ERest> void logError(E current, ERest... next)
        {
            _logger->error(current, std::forward<ERest>(next)...);
        }
        template <typename W, typename... WRest> void logWarning(W current, WRest... next)
        {
            _logger->warn(current, std::forward<WRest>(next)...);
        }
        template <typename D, typename... DRest> void logDebug(D current, DRest... next)
        {
            _logger->debug(current, std::forward<DRest>(next)...);
        }
    };

} // namespace NovelRT

#endif
