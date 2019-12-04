// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLOGGINGSERVICE_H
#define NOVELRT_NOVELLOGGINGSERVICE_H

#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace NovelRT {
enum LogLevel {
  DEBUG = SPDLOG_LEVEL_DEBUG,
  INFO = SPDLOG_LEVEL_INFO,
  WARN = SPDLOG_LEVEL_WARN,
  ERR = SPDLOG_LEVEL_ERROR,
  OFF = SPDLOG_LEVEL_OFF
};
class NovelLoggingService {
private:
  std::shared_ptr<spdlog::logger> _logger;

public:
  NovelLoggingService();
  NovelLoggingService(const std::string& core);
  NovelLoggingService(const std::string& core, LogLevel level);
  void log(const std::string& message, LogLevel level);
  void logInfoLine(const std::string& message);
  void logErrorLine(const std::string& message);
  template <typename T, typename ... TRest> void logInfo(T current, TRest ... next);
  template <typename E, typename ... ERest> void logError(E current, ERest ... next);
  void logWarning(const std::string& message);
  void logDebug(const std::string& message);
  void logInternal(const std::string& message, LogLevel level);
  void setLogLevel(LogLevel level);

};

}

#endif
