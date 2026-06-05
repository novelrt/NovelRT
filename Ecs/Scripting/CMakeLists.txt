include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Scripting

  SOURCES
    PRIVATE
      DecisionTreeStateManager.cpp
      DecisionTreeStepSystem.cpp
      EcsScriptingBuilder.cpp

      StepSystems/BranchStepSystem.cpp
      StepSystems/SpokenLineStepSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp
      include/NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp
      include/NovelRT/Ecs/Scripting/Components/DecisionTreeChoice.hpp

      include/NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp
      include/NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp
      include/NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp
      include/NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp

      include/NovelRT/Ecs/Scripting/StepSystems/BranchStepSystem.hpp
      include/NovelRT/Ecs/Scripting/StepSystems/SpokenLineStepSystem.hpp
)
