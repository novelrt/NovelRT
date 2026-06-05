// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <vector>

NovelRT::Ecs::Scripting::EcsScriptingBuilder::EcsScriptingBuilder()
    : _scriptManager{nullptr},
      _defaultActiveDecisionTreeComponent{nullptr},
      _defaultDecisionTreeChoiceComponent{std::numeric_limits<size_t>::max()},
      _defaultStepDecisionTreeChoiceComponent{std::numeric_limits<DecisionTreeStepKind>::max()}
{ }

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::WithScriptManager(std::shared_ptr<NovelRT::Scripting::ScriptManager>& manager)
{
    _scriptManager = manager;
    return *this;
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::WithDecisionTreeLoadingSystem(std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager> &)> factory)
{
    _loadingSystemFactory = factory;
    return *this;
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::WithDecisionTreeStepSystem(std::function<std::shared_ptr<DecisionTreeStepSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager> &,DecisionTreeStepManager&)> factory)
{
    _stepSystemFactory = factory;
    return *this;
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::ConfigureStepKinds(std::function<void(DecisionTreeStepManager&)> configure)
{
    configure(_stepManager);
    return *this;
}

void NovelRT::Ecs::Scripting::EcsScriptingBuilder::operator()(SystemScheduler& scheduler)
{
    auto& cache = scheduler.GetComponentCache();

    cache.RegisterComponentType(_defaultActiveDecisionTreeComponent, "NovelRT::Ecs::Scripting::ActiveDecisionTree");
    cache.RegisterComponentType(_defaultDecisionTreeChoiceComponent, "NovelRT::Ecs::Scripting::DecisionTreeChoice");
    cache.RegisterComponentType(_defaultStepDecisionTreeChoiceComponent, "NovelRT::Ecs::Scripting::StepDecisionTree");

    //auto loadingSystem = scheduler.RegisterSystem(_loadingSystemFactory(_scriptManager));
    auto stepSystem = scheduler.RegisterSystem(_stepSystemFactory(_scriptManager, _stepManager));//, std::vector<NovelRT::Ecs::SystemId>{ loadingSystem });
    unused(stepSystem);
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::AddScripting(SystemSchedulerBuilder& builder)
{
    return builder.Configure(EcsScriptingBuilder{});
}
