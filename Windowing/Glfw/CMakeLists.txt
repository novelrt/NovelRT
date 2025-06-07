include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Windowing::Glfw
  DEPENDS
    NovelRT::Base
    NovelRT::Graphics::Core
    NovelRT::Windowing::Core

  OPTIONAL_DEPENDS
    NovelRT::Graphics::Vulkan

  SOURCES
    PRIVATE
      GlfwWindowProvider.cpp
      $<$<TARGET_EXISTS:NovelRT::Graphics::Vulkan>:Vulkan/GlfwWindowProviderVulkanGraphicsProvider.cpp>

  HEADERS
    PUBLIC
      include/NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp

  LINK_LIBRARIES
    PUBLIC
      glfw)
