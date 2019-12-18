// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include "NovelLoggingService.h"
#include "NovelUtilities.h"
#include "spdlog/async.h"
#include <typeinfo>

namespace NovelRT {

  NovelLoggingService::NovelLoggingService() {
    try {
      _logger = spdlog::get(NovelUtilities::CONSOLE_LOG_GENERIC);
      if (_logger == nullptr) {
          _logger = spdlog::stdout_color_mt<spdlog::async_factory>(NovelUtilities::CONSOLE_LOG_GENERIC);
      }

      #ifndef NDEBUG
      setLogLevel(LogLevel::Debug);
      #else
      setLogLevel(LogLevel::Info);
      #endif

      //Set spdlog's error handler in case it fails.
      spdlog::set_error_handler([](const std::string& msg) {
          std::cerr << "SPDLOG ERROR: " << msg << std::endl;
      });
    } catch (const spdlog::spdlog_ex& ex) {
      std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
    }
  }

  NovelLoggingService::NovelLoggingService(const std::string& core) {
    try
    {
      _logger = spdlog::get(core);
      if (_logger == nullptr) {
        _logger = spdlog::stdout_color_mt<spdlog::async_factory>(core);
      }

    #ifndef NDEBUG
      setLogLevel(LogLevel::Debug);
    #else
      setLogLevel(LogLevel::Info);
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

  NovelLoggingService::NovelLoggingService(const std::string& core, LogLevel level) {
    try {
      _logger = spdlog::get(core);
      if (_logger == nullptr) {
        _logger = spdlog::stdout_color_mt<spdlog::async_factory>(core);
      }

      setLogLevel(level);

      //Set spdlog's error handler in case it fails.
      spdlog::set_error_handler([](const std::string& msg) {
        std::cerr << "SPDLOG ERROR: " << msg << std::endl;
      });
    }
    catch (const spdlog::spdlog_ex & ex) {
      std::cout << "Log System failed to initialize: " << ex.what() << std::endl;
    }
  }

  void NovelLoggingService::log(const std::string& message, LogLevel level) {
    switch (level) {
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
      default:
        break;
    }
  }

  void NovelLoggingService::logInfoLine(const std::string& message) {
    _logger->info(message);
  }

  void NovelLoggingService::logErrorLine(const std::string& message) {
    _logger->error(message);
  }

  void NovelLoggingService::logWarningLine(const std::string& message) {
    _logger->warn(message);
  }

  void NovelLoggingService::logDebugLine(const std::string& message) {
    _logger->debug(message);
  }

  void NovelLoggingService::logInternal(const std::string& message, LogLevel level) {
  #ifndef NDEBUG
    log(message, level);
  #endif
  }

  void NovelLoggingService::setLogLevel(LogLevel level) {
    switch (level) {
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
      default:
        _logger->set_level(spdlog::level::level_enum::info);
        _logger->info("Logging level invalid! Defaulting to INFO.");
        break;
    }
  }
}
