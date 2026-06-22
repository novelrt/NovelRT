// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/Branch.hpp>
#include <NovelRT/Ecs/Scripting/Components/BranchChoice.hpp>
#include <NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>
#include <NovelRT/Ecs/Scripting/StepSystems/BranchStepSystem.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/Statuses/Branch.hpp>

#include <algorithm>
#include <limits>

NovelRT::Ecs::Scripting::BranchStepSystem::BranchStepSystem(DecisionTreeStateManager& stateManager,
                                                            SystemScheduler& scheduler)
    : NovelRT::Ecs::Scripting::DecisionTreeStepSystem(stateManager)
{
    auto& cache = scheduler.GetComponentCache();

    cache.RegisterComponentType(Components::Branch{nullptr, nullptr}, "NovelRT::Ecs::Scripting::Branch");
    cache.RegisterComponentType(Components::BranchChoice{std::numeric_limits<std::size_t>::max()},
                                "NovelRT::Ecs::Scripting::BranchChoice");

    stateManager.RegisterStateHandler(
        [](auto& status, auto& catalogue, auto entityId)
        {
            // This is just a small helper function to avoid calling GetOptions twice
            auto makeVector = [](std::span<const std::string> original)
            { return new std::vector<std::string>(original.begin(), original.end()); };

            auto branchComponents = catalogue.template GetComponentView<Components::Branch>();

            if (auto* branch = dynamic_cast<NovelRT::Scripting::Statuses::Branch*>(status.get()))
            {
                branchComponents.PushComponentUpdateInstruction(
                    entityId,
                    Components::Branch{new std::string(branch->GetPrompt()), makeVector(branch->GetOptions())});

                return true;
            }

            return false;
        });
}

void NovelRT::Ecs::Scripting::BranchStepSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    // TODO: it would be nice to express this query as "has all of these"
    auto [decisionTrees, branchComponents, continueComponents, branchChoiceComponents] =
        catalogue.GetComponentViews<Components::ActiveDecisionTree, Components::Branch,
                                    Components::ContinueDecisionTree, Components::BranchChoice>();

    for (auto [entity, _] : continueComponents)
    {
        if (!decisionTrees.HasComponent(entity) || !branchComponents.HasComponent(entity) ||
            !branchChoiceComponents.HasComponent(entity))
        {
            continue;
        }

        auto* decisionTree = decisionTrees.GetComponent(entity).decisionTree;
        auto choice = branchChoiceComponents.GetComponent(entity).choiceIndex;

        if (auto* branch = dynamic_cast<NovelRT::Scripting::Statuses::Branch*>(decisionTree->get()))
        {
            Continue(catalogue, entity, branch->Continue(choice));
        }

        branchComponents.RemoveComponent(entity);
        continueComponents.RemoveComponent(entity);
        branchChoiceComponents.RemoveComponent(entity);
    }
}
