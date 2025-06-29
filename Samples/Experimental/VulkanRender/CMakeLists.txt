include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::VulkanRender
  DEPENDS
    NovelRT::Graphics
    NovelRT::Graphics::Vulkan
    NovelRT::Windowing

  SOURCES
    PRIVATE
      main.cpp

  RESOURCES
    PRIVATE
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv
)
