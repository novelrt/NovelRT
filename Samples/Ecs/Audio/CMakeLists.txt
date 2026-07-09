include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::AudioTest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::UI
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::Audio
    NovelRT::Windowing
    NovelRT::Input
    NovelRT::ResourceManagement::Desktop
    NovelRT::Audio::OpenAL

  SOURCES
    main.cpp
  
  RESOURCES
    Resources/Fonts/Raleway-Regular.ttf
    Resources/Shaders/imgui_frag.spv
    Resources/Shaders/imgui_vert.spv
    Resources/Shaders/vulkanrenderfrag.spv
    Resources/Shaders/vulkanrendervert.spv
    Resources/Shaders/SpritePixel.spv
    Resources/Shaders/SpriteVertex.spv
    Resources/Images/milk-carton-hi.png
    Resources/Sounds/light-rain.wav
)
