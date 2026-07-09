include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Timing
  DEPENDS
    NovelRT::Utilities

  SOURCES
    GameClock.cpp
    StepTimer.cpp

  HEADERS
    include/NovelRT/Timing/StepTimer.hpp
    include/NovelRT/Timing/Timestamp.hpp

  LINK_LIBRARIES
    PUBLIC
      spdlog::spdlog)
