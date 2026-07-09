include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting::Core
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::ResourceManagement::Desktop
    NovelRT::Scripting

  SOURCES
    StepSystems/BranchStepSystem.cpp
    StepSystems/SpokenLineStepSystem.cpp

    DecisionTreeLoadingSystem.cpp
    DecisionTreeStateManager.cpp
    DecisionTreeStepSystem.cpp
    EcsScriptingBuilder.cpp

  HEADERS
    include/NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp
    include/NovelRT/Ecs/Scripting/Components/Branch.hpp
    include/NovelRT/Ecs/Scripting/Components/BranchChoice.hpp
    include/NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp
    include/NovelRT/Ecs/Scripting/Components/DecisionTreeLoadRequest.hpp
    include/NovelRT/Ecs/Scripting/Components/LoadedDecisionTree.hpp
    include/NovelRT/Ecs/Scripting/Components/Pose.hpp
    include/NovelRT/Ecs/Scripting/Components/SpokenLine.hpp

    include/NovelRT/Ecs/Scripting/StepSystems/BranchStepSystem.hpp
    include/NovelRT/Ecs/Scripting/StepSystems/SpokenLineStepSystem.hpp

    include/NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp
    include/NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp
    include/NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp
    include/NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp
)
