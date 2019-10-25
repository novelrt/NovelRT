// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLOGGINGSERVICE_H
#define NOVELRT_NOVELLOGGINGSERVICE_H

#include <iostream>
#include "spdlog/sinks/stdout_color_sinks.h"

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

public:
  //const std::string CONSOLE_LOG = "NovelRT_Console_Log";
  NovelLoggingService();
  NovelLoggingService(LogLevel level);
  void log(std::string message, LogLevel level);
  void logInternal(std::string message, LogLevel level);
  void setLogLevel(LogLevel level);
  std::shared_ptr<spdlog::logger> NovelLoggingService::getLogger(std::string name);
};

}

#endif
