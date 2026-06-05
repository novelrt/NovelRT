// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/SpokenLine.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/SpokenLineStepSystem.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/Statuses/SpokenLine.hpp>

NovelRT::Ecs::Scripting::SpokenLineStepSystem::SpokenLineStepSystem(DecisionTreeStateManager& stateManager, SystemScheduler& scheduler)
    : NovelRT::Ecs::Scripting::DecisionTreeStepSystem(stateManager)
{
    auto& cache = scheduler.GetComponentCache();

    cache.RegisterComponentType(Components::SpokenLine{nullptr, nullptr}, "NovelRT::Ecs::Scripting::SpokenLine");

    stateManager.RegisterStateHandler([](auto& status, auto& catalogue, auto entityId)
    {
        auto spokenLineComponents = catalogue.template GetComponentView<Components::SpokenLine>();

        if (auto* spokenLine = dynamic_cast<NovelRT::Scripting::Statuses::SpokenLine*>(status.get()))
        {
            spokenLineComponents.PushComponentUpdateInstruction(entityId, Components::SpokenLine{
                new std::string(spokenLine->GetSpeaker()),
                new std::string(spokenLine->GetText())
            });

            return true;
        }

        return false;
    });
}

void NovelRT::Ecs::Scripting::SpokenLineStepSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    // TODO: it would be nice to express this query as "has all of these"
    auto [ decisionTrees, spokenLineComponents, continueComponents ] = catalogue.GetComponentViews<Components::ActiveDecisionTree, Components::SpokenLine, Components::ContinueDecisionTree>();

    for (auto [entity, _] : continueComponents)
    {
        if (!decisionTrees.HasComponent(entity) || !spokenLineComponents.HasComponent(entity))
        {
            continue;
        }

        auto* decisionTree = decisionTrees.GetComponent(entity).decisionTree;

        if (auto* spokenLine = dynamic_cast<NovelRT::Scripting::Statuses::SpokenLine*>(decisionTree->get()))
        {
            Continue(catalogue, entity, spokenLine->Continue());
        }

        spokenLineComponents.RemoveComponent(entity);
        continueComponents.RemoveComponent(entity);
    }
}
