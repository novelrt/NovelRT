// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/DecisionTreeChoice.hpp>

#include <NovelRT/Ecs/Scripting/DecisionTreeStepManager.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>
#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>

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

    NovelRT::Ecs::Scripting::DecisionTreeStepKind stepSpokenLine;
    NovelRT::Ecs::Scripting::DecisionTreeStepKind stepBranch;

    AddDefaults(builder);
    AddScripting(builder)
        .WithScriptManager(scriptManager)
        .WithDecisionTreeStepSystem([](auto&, auto& stepKindManager)
        {
            return std::make_shared<DecisionTreeStepSystem>(stepKindManager);
        })
        .ConfigureStepKinds([&stepSpokenLine, &stepBranch](auto& manager)
        {
            // TODO: we'd ideally have these as some sort of default with the ability to override
            stepSpokenLine = manager.RegisterStepHandler([](auto& catalogue, auto entityId, auto& status)
            {
                auto activeTree = catalogue.template GetComponentView<NovelRT::Ecs::Scripting::Components::ActiveDecisionTree>();

                if (auto* spokenLine = dynamic_cast<NovelRT::Scripting::Statuses::SpokenLine*>(status.get()))
                {
                    activeTree.PushComponentUpdateInstruction(entityId, NovelRT::Ecs::Scripting::Components::ActiveDecisionTree{
                        new std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>(spokenLine->Continue())
                    });
                }
            });

            stepBranch = manager.RegisterStepHandler([](auto& catalogue, auto entityId, auto& status)
            {
                auto [activeTree, choice] = catalogue.template GetComponentViews<NovelRT::Ecs::Scripting::Components::ActiveDecisionTree, NovelRT::Ecs::Scripting::Components::DecisionTreeChoice>();

                if (!choice.HasComponent(entityId))
                {
                    return;
                }

                if (auto* branch = dynamic_cast<NovelRT::Scripting::Statuses::Branch*>(status.get()))
                {
                    size_t choiceIndex = choice.GetComponent(entityId).choiceIndex;

                    activeTree.PushComponentUpdateInstruction(entityId, NovelRT::Ecs::Scripting::Components::ActiveDecisionTree{
                        new std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>(branch->Continue(choiceIndex))
                    });
                }
            });
        });

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
