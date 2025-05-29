include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Base
  SOURCES
    PRIVATE
      Atom.cpp

      Logging/LoggingService.cpp

      Threading/VolatileState.cpp

      Timing/GameClock.cpp
      Timing/StepTimer.cpp

      Utilities/Paths.cpp
      Utilities/Strings.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Utilities/BitCast.hpp
      include/NovelRT/Utilities/Lazy.hpp
      include/NovelRT/Utilities/Operators.hpp
      include/NovelRT/Utilities/Span.hpp

  LINK_LIBRARIES
    PUBLIC
      glm::glm-header-only
      Microsoft.GSL::GSL
      spdlog::spdlog
      TBB::tbb)
