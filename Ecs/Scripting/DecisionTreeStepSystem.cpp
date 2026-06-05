#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/StepDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

NovelRT::Ecs::Scripting::DecisionTreeStepSystem::DecisionTreeStepSystem(DecisionTreeStepManager stepManager)
    : _stepManager{std::move(stepManager)}
{
}

void NovelRT::Ecs::Scripting::DecisionTreeStepSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    auto [ activeTrees, stepInstructions ] = catalogue.GetComponentViews<Components::ActiveDecisionTree, Components::StepDecisionTree>();

    for (auto [entity, component] : stepInstructions)
    {
        if (!activeTrees.HasComponent(entity))
        {
            // Ignore any components which don't have an active tree
            continue;
        }

        auto& handler = _stepManager.GetStepHandler(component.stepKind);
        auto* tree = activeTrees.GetComponent(entity).decisionTree;

        // Invoke the user-registered logic for this step instruction.
        handler(catalogue, entity, *tree);
    }

    // Remove the step components so that we don't try to step repeatedly.
    stepInstructions.RemoveAllComponents();
}
