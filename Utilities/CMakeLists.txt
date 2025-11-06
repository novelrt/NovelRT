include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Utilities
  DEPENDS
    NovelRT::Exceptions

  SOURCES
    PUBLIC
      Public/Atom.cpp
      Public/BitCast.cpp
      Public/Event.cpp
      Public/Lazy.cpp
      #Public/Macros.cpp
      Public/Memory.cpp
      Public/ObjectPool.cpp
      #Public/Operators.cpp
      Public/Paths.cpp
      Public/Span.cpp
      Public/Strings.cpp
      Public/Utilities.cpp

  LINK_LIBRARIES
    PRIVATE
      Microsoft.GSL::GSL
      TBB::tbb

    PRIVATE
      "$<$<PLATFORM_ID:Darwin,iOS,tvOS,visionOS,watchOS>:$<LINK_LIBRARY:FRAMEWORK,CoreFoundation>>")
