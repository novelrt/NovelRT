include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs
  DEPENDS
    NovelRT::Ecs::Core

  OPTIONAL_DEPENDS
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::UI
    NovelRT::Ecs::Scripting
)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(UI)
add_subdirectory(Scripting)
