include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs
  DEPENDS
    NovelRT::Ecs::Core

  OPTIONAL_DEPENDS
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::UI
)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(UI)
