include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Utilities
  DEPENDS
    NovelRT::Exceptions

  SOURCES
    PRIVATE
      Atom.cpp
      Paths.cpp
      Strings.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Utilities/Atom.hpp
      include/NovelRT/Utilities/BitCast.hpp
      include/NovelRT/Utilities/Event.hpp
      include/NovelRT/Utilities/Lazy.hpp
      include/NovelRT/Utilities/Macros.hpp
      include/NovelRT/Utilities/Operators.hpp
      include/NovelRT/Utilities/Paths.hpp
      include/NovelRT/Utilities/Span.hpp
      include/NovelRT/Utilities/Strings.hpp

  LINK_LIBRARIES
    PUBLIC
      Microsoft.GSL::GSL
      TBB::tbb

    PRIVATE
      "$<$<PLATFORM_ID:Darwin,iOS,tvOS,visionOS,watchOS>:$<LINK_LIBRARY:FRAMEWORK,CoreFoundation>>")
