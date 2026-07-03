include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Logging
  DEPENDS
    NovelRT::Exceptions
    NovelRT::Utilities

  SOURCES
    LoggingService.cpp

  HEADERS
    include/NovelRT/Logging/BuiltInLogSections.hpp
    include/NovelRT/Logging/LoggingService.hpp

  LINK_LIBRARIES
    PUBLIC
      spdlog::spdlog)
