include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Scripting

  SOURCES
    PRIVATE
      DecisionTreeStepManager.cpp
      DecisionTreeStepSystem.cpp
      EcsScriptingBuilder.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp
      include/NovelRT/Ecs/Scripting/Components/StepDecisionTree.hpp
      include/NovelRT/Ecs/Scripting/Components/DecisionTreeChoice.hpp

      include/NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp
      include/NovelRT/Ecs/Scripting/DecisionTreeStepManager.hpp
      include/NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp
      include/NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp
)
