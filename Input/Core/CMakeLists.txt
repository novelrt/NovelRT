include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Input::Core
  DEPENDS
    NovelRT::Base

    NovelRT::Windowing::Core

  SOURCES
    PRIVATE
      KeyStateFrameChangeLog.cpp
      NovelKey.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Input/InputAction.hpp
      include/NovelRT/Input/InputProvider.hpp
      include/NovelRT/Input/KeyState.hpp
      include/NovelRT/Input/KeyStateFrameChangeLog.hpp
      include/NovelRT/Input/NovelKey.hpp
)
