include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Windowing::Glfw
  DEPENDS
    NovelRT::Base
    NovelRT::Graphics::Core
    NovelRT::Windowing::Core

  SOURCES
    PRIVATE
      GlfwWindowingDevice.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Windowing/Glfw/GlfwWindowingDevice.hpp

  LINK_LIBRARIES
    PRIVATE
      glfw)
