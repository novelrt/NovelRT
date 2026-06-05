#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/DecisionTreeChoice.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>

#include <NovelRT/Scripting/ScriptManager.hpp>

#include <functional>
#include <memory>

namespace NovelRT::Ecs::Scripting
{
    class DecisionTreeLoadingSystem;
    class DecisionTreeStepSystem;

    class EcsScriptingBuilder
    {
    private:
        DecisionTreeStateManager _stateManager;

        std::shared_ptr<NovelRT::Scripting::ScriptManager> _scriptManager;
        std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)> _loadingSystemFactory;
        std::vector<std::function<std::shared_ptr<DecisionTreeStepSystem>(DecisionTreeStateManager&,SystemScheduler&)>> _stepSystemFactories;

        Components::ActiveDecisionTree _defaultActiveDecisionTreeComponent;
        Components::ContinueDecisionTree _defaultContinueDecisionTreeChoiceComponent;

        EcsScriptingBuilder();

        friend EcsScriptingBuilder& AddScripting(SystemSchedulerBuilder&);
    public:
        EcsScriptingBuilder(const EcsScriptingBuilder& other) = default;
        EcsScriptingBuilder& operator=(const EcsScriptingBuilder& other) = default;
        EcsScriptingBuilder(EcsScriptingBuilder&& other) = default;
        EcsScriptingBuilder& operator=(EcsScriptingBuilder&& other) = default;
        ~EcsScriptingBuilder() = default;


        EcsScriptingBuilder& WithScriptManager(std::shared_ptr<NovelRT::Scripting::ScriptManager>&);
        EcsScriptingBuilder& WithDecisionTreeLoadingSystem(std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)>);

        EcsScriptingBuilder& RegisterStepSystem(std::function<std::shared_ptr<DecisionTreeStepSystem>(DecisionTreeStateManager&,SystemScheduler&)> factory);

        void operator()(SystemScheduler&);
    };

    EcsScriptingBuilder& AddScripting(SystemSchedulerBuilder& builder);
}
