include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting
  DEPENDS
    NovelRT::Ecs::Scripting::Core

  OPTIONAL_DEPENDS
    NovelRT::Ecs::Scripting::Graphics)

add_subdirectory(Core)
# add_subdirectory(Graphics)
