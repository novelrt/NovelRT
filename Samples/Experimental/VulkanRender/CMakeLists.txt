include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::VulkanRender
  DEPENDS
    NovelRT::Graphics
    NovelRT::Graphics::Vulkan
    NovelRT::Windowing
    NovelRT::ResourceManagement

  SOURCES
    main.cpp

  RESOURCES
    Resources/Shaders/vulkanrenderfrag.spv
    Resources/Shaders/vulkanrendervert.spv
)
