// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/SpokenLine.hpp>
#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UIElement.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>

#include <NovelRT/Ecs/Scripting/UI/SpokenLineTranslationSystem.hpp>

void NovelRT::Ecs::Scripting::UI::SpokenLineTranslationSystem::CleanupInactiveTrees(Catalogue& catalogue)
{
    auto trees = catalogue.GetComponentView<Components::ActiveDecisionTree>();

    for (auto it = _activeTrees.begin(), end = _activeTrees.end(); it != end;)
    {
        if (trees.HasComponent(it->first))
        {
            ++it;
            continue;
        }

        catalogue.DeleteEntity(it->second.container);
        catalogue.DeleteEntity(it->second.message);
        catalogue.DeleteEntity(it->second.next);

        it = _activeTrees.erase(it);
    }
}

void NovelRT::Ecs::Scripting::UI::SpokenLineTranslationSystem::IdentifyNewTrees(Catalogue& catalogue)
{
    auto [trees, transforms, graphComponents, uiButtons] = catalogue.GetComponentViews<NovelRT::Ecs::Scripting::Components::ActiveDecisionTree, NovelRT::Ecs::Components::TransformComponent, NovelRT::Ecs::Components::EntityGraphComponent, NovelRT::Ecs::UI::Components::UIButton>();

    for (auto [entity, _] : trees)
    {
        auto it = _activeTrees.find(entity);
        if (it != _activeTrees.end())
        {
            continue;
        }

        it = _activeTrees.emplace_hint(it, entity, TreeInfo{
            .container = catalogue.CreateEntity(),
            .message = catalogue.CreateEntity(),
            .next = catalogue.CreateEntity()
        });

        uiButtons.PushComponentUpdateInstruction(it->second.next, NovelRT::Ecs::UI::Components::UIButton {
            .label = new std::string("Next"),
            .eventId = 0,
            .bgColour = {0, 102, 204, 255},
            .activeColour = {0, 82, 163, 255},
            .hoveredColour = {0, 119, 255, 255},
            .textColour = {255, 255, 255, 255},
        });

        // TODO: this should be set elsewhere
        transforms.PushComponentUpdateInstruction(it->second.container, NovelRT::Ecs::Components::TransformComponent{
            .position = {350.0f, 500.0f},
            .scale = {612.0f, 200.0f},
            .rotationInRadians = 0.0f
        });
        transforms.PushComponentUpdateInstruction(it->second.next, NovelRT::Ecs::Components::TransformComponent{
            .position = {500.0f, 150.0f},
            .scale = {82.0f, 30.0f},
            .rotationInRadians = 0.0f
        });

        NovelRT::Ecs::EntityGraphView relations{catalogue, it->second.container, NovelRT::Ecs::Components::EntityGraphComponent{}};
        relations.AddInsertChildInstruction(it->second.message);
        relations.AddInsertChildInstruction(it->second.next);
        relations.Commit();
    }
}

void NovelRT::Ecs::Scripting::UI::SpokenLineTranslationSystem::UpdateContainers(Catalogue& catalogue)
{
    auto [spokenLines, continues, uiClickEvents, uiElements, uiTexts, uiWidgetContainers] = catalogue.GetComponentViews<Components::SpokenLine, Components::ContinueDecisionTree, NovelRT::Ecs::UI::Components::UIClickEvent, NovelRT::Ecs::UI::Components::UIElement, NovelRT::Ecs::UI::Components::UIText, NovelRT::Ecs::UI::Components::UIWidgetContainer>();

    for (auto& [entity, info] : _activeTrees)
    {
        if (spokenLines.HasComponent(entity))
        {
            uiElements.PushComponentUpdateInstruction(info.container, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Container
            });

            uiElements.PushComponentUpdateInstruction(info.message, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Text
            });

            uiElements.PushComponentUpdateInstruction(info.next, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Button
            });

            std::string message = *spokenLines.GetComponent(entity).message;
            uiTexts.PushComponentUpdateInstruction(info.message, NovelRT::Ecs::UI::Components::UIText {
                .textValue = new std::string(message),
                .colour = {255, 255, 255, 255}
            });

            //std::string speaker = *spokenLines.GetComponent(entity).speaker;
            uiWidgetContainers.PushComponentUpdateInstruction(info.container, NovelRT::Ecs::UI::Components::UIWidgetContainer {
                .title = new std::string("Message")
            });
        }
        else
        {
            uiElements.RemoveComponent(info.container);
            uiElements.RemoveComponent(info.message);
            uiElements.RemoveComponent(info.next);
        }

        if (uiClickEvents.HasComponent(info.next))
        {
            uiClickEvents.RemoveComponent(info.next);
            continues.PushComponentUpdateInstruction(entity, Components::ContinueDecisionTree{});
        }
    }
}

NovelRT::Ecs::Scripting::UI::SpokenLineTranslationSystem::SpokenLineTranslationSystem()
{ }

void NovelRT::Ecs::Scripting::UI::SpokenLineTranslationSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    CleanupInactiveTrees(catalogue);
    IdentifyNewTrees(catalogue);

    UpdateContainers(catalogue);
}
