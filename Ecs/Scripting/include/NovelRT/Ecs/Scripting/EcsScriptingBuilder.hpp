#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

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
        std::shared_ptr<NovelRT::Scripting::ScriptManager> _scriptManager;
        std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)> _loadingSystemFactory;
        std::function<std::shared_ptr<DecisionTreeStepSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)> _stepSystemFactory;

        EcsScriptingBuilder();

        friend EcsScriptingBuilder& AddScripting(SystemSchedulerBuilder&);
    public:

        EcsScriptingBuilder& WithScriptManager(std::shared_ptr<NovelRT::Scripting::ScriptManager>&);
        EcsScriptingBuilder& WithDecisionTreeLoadingSystem(std::function<std::shared_ptr<DecisionTreeLoadingSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)>);
        EcsScriptingBuilder& WithDecisionTreeStepSystem(std::function<std::shared_ptr<DecisionTreeStepSystem>(std::shared_ptr<NovelRT::Scripting::ScriptManager>&)>);

        void operator()(SystemScheduler&);
    };

    EcsScriptingBuilder& AddScripting(SystemSchedulerBuilder& builder);
}
