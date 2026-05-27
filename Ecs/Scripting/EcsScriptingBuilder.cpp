// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <vector>

NovelRT::Ecs::Scripting::EcsScriptingBuilder::EcsScriptingBuilder()
    : _scriptManager{nullptr}
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

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::EcsScriptingBuilder::WithDecisionTreeStepSystem(std::function<std::shared_ptr<DecisionTreeStepSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager> &)> factory)
{
    _stepSystemFactory = factory;
    return *this;
}

void NovelRT::Ecs::Scripting::EcsScriptingBuilder::operator()(SystemScheduler& scheduler)
{
    auto loadingSystem = scheduler.RegisterSystem(_loadingSystemFactory(_scriptManager));
    auto stepSystem = scheduler.RegisterSystem(_stepSystemFactory(_scriptManager), std::vector<NovelRT::Ecs::SystemId>{ loadingSystem });
}

NovelRT::Ecs::Scripting::EcsScriptingBuilder& NovelRT::Ecs::Scripting::AddScripting(SystemSchedulerBuilder& builder)
{
    return builder.Configure(EcsScriptingBuilder{});
}
