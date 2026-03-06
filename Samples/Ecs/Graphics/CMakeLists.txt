include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::GraphicsEcsTest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Graphics
    NovelRT::Windowing

  SOURCES
    PRIVATE
      main.cpp
)
