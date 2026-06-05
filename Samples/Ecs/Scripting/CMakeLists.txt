include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Ecs::ScriptingEcsTest
  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Scripting
    NovelRT::ResourceManagement::Desktop

  SOURCES
    PRIVATE
      main.cpp
)
