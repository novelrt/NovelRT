include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::LuaOnlyTargets::VisualNovel
  MACOSX_BUNDLE

  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::Scripting
    NovelRT::ResourceManagement::Desktop

  SOURCES
    main.cpp

  RESOURCES
    Resources/Fonts/Raleway-Regular.ttf
    Resources/Images/Milk.png
    Resources/Images/novel-chan.png
    Resources/Scripts/Sample.lua
    Resources/Shaders/imgui_frag.spv
    Resources/Shaders/imgui_vert.spv
    Resources/Shaders/vulkanrenderfrag.spv
    Resources/Shaders/vulkanrendervert.spv
    Resources/Shaders/SpritePixel.spv
    Resources/Shaders/SpriteVertex.spv
    Resources/VNConfig.json
    Resources/Images/SampleBG.png
)
