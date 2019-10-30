// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelLoggingService.h"
#include "NovelRTUtilities.h"
#include "spdlog/async.h"

namespace NovelRT {

NovelLoggingService::NovelLoggingService() {
  try
  {
    _console = spdlog::get(NovelUtilities::CONSOLE_LOG_GENERIC);
    if (_console == nullptr)
    {
        _console = spdlog::stdout_color_mt<spdlog::async_factory>(NovelUtilities::CONSOLE_LOG_GENERIC);
    }

    #ifndef NDEBUG
    setLogLevel(LogLevel::DEBUG);
    #else
    setLogLevel(LogLevel::INFO);
    #endif

    //Set spdlog's error handler in case it fails.
     spdlog::set_error_handler([](const std::string& msg) {
        std::cerr << "SPDLOG ERROR: " << msg << std::endl;
    });
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
  }
}

NovelLoggingService::NovelLoggingService(std::string core) {
  try
  {
    _console = spdlog::get(core);
    if (_console == nullptr)
    {
      _console = spdlog::stdout_color_mt<spdlog::async_factory>(core);
    }

#ifndef NDEBUG
    setLogLevel(LogLevel::DEBUG);
#else
    setLogLevel(LogLevel::INFO);
#endif

    //Set spdlog's error handler in case it fails.
    spdlog::set_error_handler([](const std::string& msg) {
      std::cerr << "SPDLOG ERROR: " << msg << std::endl;
    });
  }
  catch (const spdlog::spdlog_ex & ex)
  {
    std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
  }
}

NovelLoggingService::NovelLoggingService(std::string core, LogLevel level) {
  try
  {
    _console = spdlog::get(core);
    if (_console == nullptr)
    {
      _console = spdlog::stdout_color_mt<spdlog::async_factory>(core);
    }

    setLogLevel(level);

    //Set spdlog's error handler in case it fails.
    spdlog::set_error_handler([](const std::string& msg) {
      std::cerr << "SPDLOG ERROR: " << msg << std::endl;
    });
  }
  catch (const spdlog::spdlog_ex & ex)
  {
    std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
  }
}

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
