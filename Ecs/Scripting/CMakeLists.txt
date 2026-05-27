include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Scripting

  SOURCES
    PRIVATE
      EcsScriptingBuilder.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp
      include/NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp
)
