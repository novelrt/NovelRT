// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelLoggingService.h"
#include "NovelRTUtilities.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace NovelRT {

NovelLoggingService* NovelLoggingService::logPointer = NULL;

NovelLoggingService* NovelLoggingService::instance() {
  if (!logPointer)
  {
    logPointer = new NovelLoggingService;
  }

  return logPointer;
}

NovelLoggingService::NovelLoggingService() {
  try
  {
    auto console = spdlog::get(NovelUtilities::CONSOLE_LOG);
    if (!console)
    {
      console = spdlog::stdout_color_mt(NovelUtilities::CONSOLE_LOG);
    }
    #ifndef NDEBUG
    setLogLevel(LogLevel::TRACE);
    #else
    setLogLevel(LogLevel::INFO);
    #endif
    std::string lvl = spdlog::level::to_short_c_str(console->level());
    console->info("\nNovelRT\nLog System Initialized!\nLogging at level: " + lvl);
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
  }
}

/*
NovelLoggingService::NovelLoggingService(LogLevel level) {
  try
  {
    auto console = spdlog::get(NovelUtilities::CONSOLE_LOG);
    if (!console)
    {
      console = spdlog::stdout_color_mt(NovelUtilities::CONSOLE_LOG);
    }
    setLogLevel(level);
    std::string lvl = spdlog::level::to_short_c_str(console->level());
    console->info("\nNovelRT\nLog System Initialized!\nLogging at level: " + lvl);
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
  }
}
*/

void NovelLoggingService::log(std::string message, LogLevel level) {
  switch (level)
  {
  case SPDLOG_LEVEL_TRACE:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->trace(message);
    break;
  }
  case SPDLOG_LEVEL_DEBUG:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->debug(message);
    break;
  }
  case SPDLOG_LEVEL_INFO:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->info(message);
    break;
  }
  case SPDLOG_LEVEL_WARN:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->warn(message);
    break;
  }
  case SPDLOG_LEVEL_ERROR:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->error(message);
    break;
  }
  case SPDLOG_LEVEL_CRITICAL:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->critical(message);
    break;
  }
  default:
  {
    break;
  }
  }
}

void NovelLoggingService::logInternal(std::string message, LogLevel level) {
#ifndef NDEBUG
  log(message, level);
#endif
}

void NovelLoggingService::setLogLevel(LogLevel level) {
  switch (level)
  {
  case SPDLOG_LEVEL_TRACE:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::trace);
    break;
  }
  case SPDLOG_LEVEL_DEBUG:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::debug);
    break;
  }
  case SPDLOG_LEVEL_INFO:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::info);
    break;
  }
  case SPDLOG_LEVEL_WARN:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::warn);
    break;
  }
  case SPDLOG_LEVEL_ERROR:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::err);
    break;
  }
  case SPDLOG_LEVEL_CRITICAL:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::critical);
    break;
  }
  case SPDLOG_LEVEL_OFF:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::off);
    break;
  }
  default:
  {
    spdlog::get(NovelUtilities::CONSOLE_LOG)->set_level(spdlog::level::level_enum::info);
    spdlog::get(NovelUtilities::CONSOLE_LOG)->info("Logging level invalid! Defaulting to INFO.");
    break;
  }
  }
}

std::shared_ptr<spdlog::logger> NovelLoggingService::getLogger(std::string name) {
  return spdlog::get(name);
}

}
