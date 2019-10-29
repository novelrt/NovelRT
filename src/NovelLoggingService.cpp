// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelLoggingService.h"
#include "NovelRTUtilities.h"
#include "spdlog/async.h"

namespace NovelRT {

NovelLoggingService::NovelLoggingService() {
  try
  {
    _console = spdlog::get(NovelUtilities::CONSOLE_LOG);
    if (_console == nullptr)
    {
      _console = spdlog::stdout_logger_mt(NovelUtilities::CONSOLE_LOG);
      spdlog::register_logger(_console);
    }

    #ifndef NDEBUG
    setLogLevel(LogLevel::TRACE);
    #else
    setLogLevel(LogLevel::INFO);
    #endif
    std::string lvl = spdlog::level::to_short_c_str(_console->level());

     spdlog::set_error_handler([](const std::string& msg) {
        std::cerr << "SPDLOG ERROR: " << msg << std::endl;
    });
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
    auto console = _console;
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
    _console->trace(message);
    break;
  }
  case SPDLOG_LEVEL_DEBUG:
  {
    _console->debug(message);
    break;
  }
  case SPDLOG_LEVEL_INFO:
  {
    _console->info(message);
    break;
  }
  case SPDLOG_LEVEL_WARN:
  {
    _console->warn(message);
    break;
  }
  case SPDLOG_LEVEL_ERROR:
  {
    _console->error(message);
    break;
  }
  case SPDLOG_LEVEL_CRITICAL:
  {
    _console->critical(message);
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
    _console->set_level(spdlog::level::level_enum::trace);
    break;
  }
  case SPDLOG_LEVEL_DEBUG:
  {
    _console->set_level(spdlog::level::level_enum::debug);
    break;
  }
  case SPDLOG_LEVEL_INFO:
  {
    _console->set_level(spdlog::level::level_enum::info);
    break;
  }
  case SPDLOG_LEVEL_WARN:
  {
    _console->set_level(spdlog::level::level_enum::warn);
    break;
  }
  case SPDLOG_LEVEL_ERROR:
  {
    _console->set_level(spdlog::level::level_enum::err);
    break;
  }
  case SPDLOG_LEVEL_CRITICAL:
  {
    _console->set_level(spdlog::level::level_enum::critical);
    break;
  }
  case SPDLOG_LEVEL_OFF:
  {
    _console->set_level(spdlog::level::level_enum::off);
    break;
  }
  default:
  {
    _console->set_level(spdlog::level::level_enum::info);
    _console->info("Logging level invalid! Defaulting to INFO.");
    break;
  }
  }
}

}
