// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/Components/DecisionTreeLoadRequest.hpp>
#include <NovelRT/Ecs/Scripting/Components/LoadedDecisionTree.hpp>

#include <NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <vector>

NovelRT::Ecs::Scripting::EcsScriptingBuilder::EcsScriptingBuilder()
    : _scriptManager{nullptr},
      _defaultActiveDecisionTreeComponent{nullptr},
      _defaultContinueDecisionTreeChoiceComponent{false}
{
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::WithScriptManager(
    std::shared_ptr<NovelRT::Scripting::ScriptManager>& manager)
{
    _scriptManager = manager;
    return *this;
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::
    WithDecisionTreeLoadingSystem(
        std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)>
            factory)
{
    _loadingSystemFactory = factory;
    return *this;
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::RegisterStepSystem(
    std::function<std::shared_ptr<DecisionTreeStepSystem>(DecisionTreeStateManager&,SystemScheduler&)> factory)
{
    _stepSystemFactories.emplace_back(factory);
    return *this;
}

void NovelRT::Ecs::Scripting::EcsScriptingBuilder::operator()(SystemScheduler& scheduler)
{
    auto& cache = scheduler.GetComponentCache();

    cache.RegisterComponentType(_defaultActiveDecisionTreeComponent, "NovelRT::Ecs::Scripting::ActiveDecisionTree");
    cache.RegisterComponentType(_defaultContinueDecisionTreeChoiceComponent, "NovelRT::Ecs::Scripting::ContinueDecisionTree");
    cache.RegisterComponentType(Components::DecisionTreeLoadRequest{}, "NovelRT::Ecs::Scripting::DecisionTreeLoadRequest");
    cache.RegisterComponentType(Components::LoadedDecisionTree{{}, nullptr}, "NovelRT::Ecs::Scripting::LoadedDecisionTree");

    auto loadingSystem = scheduler.RegisterSystem(_loadingSystemFactory(_scriptManager));

    for (const auto& factory : _stepSystemFactories)
    {
        auto stepSystem = scheduler.RegisterSystem(factory(_stateManager, scheduler), std::vector<SystemId>{ loadingSystem });
        unused(stepSystem);
    }
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::AddScripting(SystemSchedulerBuilder& builder)
{
    return builder.Configure(EcsScriptingBuilder{});
}
