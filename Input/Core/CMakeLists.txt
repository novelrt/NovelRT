include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Input::Core
  DEPENDS
    NovelRT::Maths
    NovelRT::Timing
    NovelRT::Utilities

    NovelRT::Windowing::Core

  SOURCES
    KeyStateFrameChangeLog.cpp
    NovelKey.cpp

  HEADERS
    include/NovelRT/Input/InputAction.hpp
    include/NovelRT/Input/InputProvider.hpp
    include/NovelRT/Input/KeyState.hpp
    include/NovelRT/Input/KeyStateFrameChangeLog.hpp
    include/NovelRT/Input/NovelKey.hpp
)
