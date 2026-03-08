include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::GraphicsEcsTest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Graphics
    NovelRT::Windowing
    NovelRT::ResourceManagement::Desktop

  SOURCES
    PRIVATE
      main.cpp
  
  RESOURCES
    PUBLIC
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv
)
