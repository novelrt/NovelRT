include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs
  DEPENDS
    NovelRT::Ecs::Core
)

add_subdirectory(Core)
