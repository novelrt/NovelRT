include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::GraphicsEcsTest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Graphics
    NovelRT::Windowing
    NovelRT::ResourceManagement::Desktop

  SOURCES
    main.cpp
  
  RESOURCES
    Resources/Shaders/SpritePixel.spv
    Resources/Shaders/SpriteVertex.spv
    Resources/Images/novel-chan.png
)
