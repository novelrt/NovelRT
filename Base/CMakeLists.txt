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
      include/NovelRT/Exceptions/FileNotFoundException.hpp
      include/NovelRT/Exceptions/InitialisationFailureException.hpp
      include/NovelRT/Exceptions/InvalidOperationException.hpp
      include/NovelRT/Exceptions/KeyNotFoundException.hpp
      include/NovelRT/Exceptions/NotSupportedException.hpp
      include/NovelRT/Exceptions/NullPointerException.hpp
      include/NovelRT/Exceptions/OutOfMemoryException.hpp
      include/NovelRT/Exceptions/TimeoutException.hpp

      include/NovelRT/Logging/BuiltInLogSections.hpp
      include/NovelRT/Logging/LoggingService.hpp

      include/NovelRT/Maths/GeoVector2F.hpp
      include/NovelRT/Maths/GeoVector3F.hpp
      include/NovelRT/Maths/GeoVector4F.hpp

      include/NovelRT/Threading/VolatileState.hpp

      include/NovelRT/Timing/StepTimer.hpp
      include/NovelRT/Timing/Timestamp.hpp

      include/NovelRT/Utilities/BitCast.hpp
      include/NovelRT/Utilities/Event.hpp
      include/NovelRT/Utilities/Lazy.hpp
      include/NovelRT/Utilities/Macros.hpp
      include/NovelRT/Utilities/Operators.hpp
      include/NovelRT/Utilities/Paths.hpp
      include/NovelRT/Utilities/Span.hpp
      include/NovelRT/Utilities/Strings.hpp

      include/NovelRT/Atom.hpp

  LINK_LIBRARIES
    PUBLIC
      glm::glm-header-only
      Microsoft.GSL::GSL
      spdlog::spdlog
      TBB::tbb
    PRIVATE
      "$<$<PLATFORM_ID:Darwin,iOS,tvOS,visionOS,watchOS>:$<LINK_LIBRARY:FRAMEWORK,CoreFoundation>>")
