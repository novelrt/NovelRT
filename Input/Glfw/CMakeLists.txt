include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Input::Glfw
  DEPENDS
    NovelRT::Input::Core

    NovelRT::Windowing::Glfw
  SOURCES
    PRIVATE
      GlfwInputProvider.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Input/Glfw/GlfwInputProvider.hpp

  LINK_LIBRARIES
    PUBLIC
      glfw)
