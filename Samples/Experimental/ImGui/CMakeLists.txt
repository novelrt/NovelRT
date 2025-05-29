include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::ImGui
  DEPENDS
    NovelRT::Graphics
    NovelRT::Graphics::Vulkan
    NovelRT::Input
    NovelRT::UI
    NovelRT::Windowing

  SOURCES
    PRIVATE
      main.cpp

  RESOURCES
    PUBLIC
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv)
