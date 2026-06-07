// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/BranchStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/SpokenLineStepSystem.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Scripting;
using namespace NovelRT::Scripting;
using namespace NovelRT::Timing;
using namespace NovelRT::Utilities;

int main()
{
    SystemSchedulerBuilder builder{};

    auto scriptManager = std::make_shared<ScriptManager>();

    AddDefaults(builder);
    AddScripting(builder)
        .WithScriptManager(scriptManager)
        .RegisterStepSystem([](auto& manager, auto& scheduler)
                            { return std::make_shared<BranchStepSystem>(manager, scheduler); })
        .RegisterStepSystem([](auto& manager, auto& scheduler)
                            { return std::make_shared<SpokenLineStepSystem>(manager, scheduler); });

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer, &scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (true)
    {
        timer.Tick(TimerCallback);
    }

    return 0;
}
