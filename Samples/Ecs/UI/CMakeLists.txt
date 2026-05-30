include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::UITest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::UI
    NovelRT::Ecs::Graphics
    NovelRT::Windowing
    NovelRT::Input
    NovelRT::ResourceManagement::Desktop

  SOURCES
    PRIVATE
      main.cpp
  
  RESOURCES
    PUBLIC
      Resources/Fonts/Raleway-Regular.ttf
      Resources/Shaders/imgui_frag.spv
      Resources/Shaders/imgui_vert.spv
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv
      Resources/Shaders/SpritePixel.spv
      Resources/Shaders/SpriteVertex.spv
      Resources/Images/novel-chan.png
)
