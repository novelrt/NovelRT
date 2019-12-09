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
  inline void logDebug() {}
  inline void logWarning() {}
  inline void logError() {}
  inline void logInfo() {}

public:
  NovelLoggingService();
  NovelLoggingService(const std::string& core);
  NovelLoggingService(const std::string& core, LogLevel level);
  void log(const std::string& message, LogLevel level);
  void logInfoLine(const std::string& message);
  void logErrorLine(const std::string& message);
  void logWarningLine(const std::string& message);
  void logDebugLine(const std::string& message);
  void logInternal(const std::string& message, LogLevel level);
  void setLogLevel(LogLevel level);

  template <typename I, typename ... IRest>
  void logInfo(I current, IRest ... next) {
    _logger->info(current);
    logInfo(next ...);
  }
  template <typename E, typename ... ERest>
  void logError(E current, ERest ... next) {
  _logger->error(current);
  logError(next ...);
  }
  template <typename W, typename ... WRest>
  void logWarning(W current, WRest ... next) {
  _logger->warn(current);
  logWarning(next ...);
  }
  template <typename D, typename ... DRest>
  void logDebug(D current, DRest ... next) {
  _logger->debug(current);
  logDebug(next ...);
  }
};

}

#endif
