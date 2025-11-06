include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Logging
  DEPENDS
    NovelRT::Exceptions
    # NovelRT::Utilities

  SOURCES
    PUBLIC
      Public/LoggingService.cpp

  LINK_LIBRARIES
    PUBLIC
      spdlog::spdlog)
