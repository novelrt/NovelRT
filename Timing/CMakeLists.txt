include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Timing
  DEPENDS
    NovelRT::Utilities

  SOURCES
    PRIVATE
      GameClock.cpp
      StepTimer.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Timing/StepTimer.hpp
      include/NovelRT/Timing/Timestamp.hpp

  LINK_LIBRARIES
    PUBLIC
      spdlog::spdlog)
