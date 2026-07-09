include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Input::Glfw
  DEPENDS
    NovelRT::Input::Core
    NovelRT::Windowing::Glfw

  SOURCES
    GlfwInputProvider.cpp

  HEADERS
    include/NovelRT/Input/Glfw/GlfwInputProvider.hpp

  LINK_LIBRARIES
    PUBLIC
      glfw)
