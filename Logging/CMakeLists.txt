include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Logging
  DEPENDS
    NovelRT::Exceptions
    NovelRT::Utilities

  SOURCES
    PRIVATE
      LoggingService.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Logging/BuiltInLogSections.hpp
      include/NovelRT/Logging/LoggingService.hpp

  LINK_LIBRARIES
    PUBLIC
      spdlog::spdlog)
