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
    PUBLIC
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv
)
