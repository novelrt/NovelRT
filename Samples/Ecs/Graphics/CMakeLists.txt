include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::Graphics
  DEPENDS
    NovelRT::Ecs::Graphics
    NovelRT::Windowing
    NovelRT::ResourceManagement

  SOURCES
    PRIVATE
      main.cpp
)
