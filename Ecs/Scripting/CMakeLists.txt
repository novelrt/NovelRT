include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting
  DEPENDS
    NovelRT::Ecs::Scripting::Core

  OPTIONAL_DEPENDS
    NovelRT::Ecs::Scripting::Graphics
    NovelRT::Ecs::Scripting::UI)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(UI)
