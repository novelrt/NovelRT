include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Graphics
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Graphics

  SOURCES
    PRIVATE
      empty.cpp
)
