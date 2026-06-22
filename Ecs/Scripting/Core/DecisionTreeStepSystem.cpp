// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>

NovelRT::Ecs::Scripting::DecisionTreeStepSystem::DecisionTreeStepSystem(DecisionTreeStateManager& stepManager)
    : _stepManager{stepManager}
{
}

void NovelRT::Ecs::Scripting::DecisionTreeStepSystem::Continue(
    Catalogue& catalogue,
    EntityId entity,
    std::unique_ptr<NovelRT::Scripting::DecisionTreeStatus>&& status)
{
    auto decisionTrees = catalogue.GetComponentView<Components::ActiveDecisionTree>();

    auto* ptr = new std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>(std::move(status));
    decisionTrees.PushComponentUpdateInstruction(entity, Components::ActiveDecisionTree{ptr});
    _stepManager.HandleStateChange(catalogue, entity, *ptr);
}
