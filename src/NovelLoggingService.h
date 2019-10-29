// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLOGGINGSERVICE_H
#define NOVELRT_NOVELLOGGINGSERVICE_H

#define SPDLOG_DISABLE_TID_CACHING

#include <iostream>

#include "spdlog/sinks/stdout_sinks.h"

namespace NovelRT {
enum LogLevel {
  TRACE = SPDLOG_LEVEL_TRACE,
  DEBUG = SPDLOG_LEVEL_DEBUG,
  INFO = SPDLOG_LEVEL_INFO,
  WARN = SPDLOG_LEVEL_WARN,
  ERR = SPDLOG_LEVEL_ERROR,
  CRITICAL = SPDLOG_LEVEL_CRITICAL,
  OFF = SPDLOG_LEVEL_OFF
};

class NovelLoggingService {
private:
  std::shared_ptr<spdlog::logger> _console;

public:
  NovelLoggingService();
  ~NovelLoggingService() = default;
  void log(std::string message, LogLevel level);
  void logInternal(std::string message, LogLevel level);
  void setLogLevel(LogLevel level);
};

}

#endif
