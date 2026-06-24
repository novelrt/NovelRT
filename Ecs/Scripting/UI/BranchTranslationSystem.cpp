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
#include <NovelRT/Ecs/Scripting/Components/Branch.hpp>
#include <NovelRT/Ecs/Scripting/Components/BranchChoice.hpp>
#include <NovelRT/Ecs/Scripting/Components/ContinueDecisionTree.hpp>
#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UIElement.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>

#include <NovelRT/Ecs/Scripting/UI/BranchTranslationSystem.hpp>

void NovelRT::Ecs::Scripting::UI::BranchTranslationSystem::CleanupInactiveTrees(Catalogue& catalogue)
{
    auto trees = catalogue.GetComponentView<Components::ActiveDecisionTree>();

    for (auto it = _activeTrees.begin(), end = _activeTrees.end(); it != end;)
    {
        if (trees.HasComponent(it->first))
        {
            ++it;
            continue;
        }

        catalogue.DeleteEntity(it->second.messageContainer);
        catalogue.DeleteEntity(it->second.message);
        catalogue.DeleteEntity(it->second.choiceContainer);
        for (const auto& id : it->second.choices)
        {
            catalogue.DeleteEntity(id);
        }

        it = _activeTrees.erase(it);
    }
}

void NovelRT::Ecs::Scripting::UI::BranchTranslationSystem::IdentifyNewTrees(Catalogue& catalogue)
{
    auto [trees, transforms, uiButtons] = catalogue.GetComponentViews<NovelRT::Ecs::Scripting::Components::ActiveDecisionTree, NovelRT::Ecs::Components::TransformComponent, NovelRT::Ecs::UI::Components::UIButton>();

    for (auto [entity, _] : trees)
    {
        auto it = _activeTrees.find(entity);
        if (it != _activeTrees.end())
        {
            continue;
        }

        it = _activeTrees.emplace_hint(it, entity, TreeInfo{
            .messageContainer = catalogue.CreateEntity(),
            .message = catalogue.CreateEntity(),
            .choiceContainer = catalogue.CreateEntity(),
            .choices = {}
        });

        // TODO: this should be set elsewhere
        transforms.PushComponentUpdateInstruction(it->second.messageContainer, NovelRT::Ecs::Components::TransformComponent{
            .position = {320.0f, 860.0f},
            .scale = {1280.0f, 200.0f},
            .rotationInRadians = 0.0f
        });

        transforms.PushComponentUpdateInstruction(it->second.choiceContainer, NovelRT::Ecs::Components::TransformComponent{
            .position = {320.0f, 20.0f},
            .scale = {1280.0f, 820.0f},
            .rotationInRadians = 0.0f
        });

        NovelRT::Ecs::EntityGraphView messageRelations{catalogue, it->second.messageContainer, NovelRT::Ecs::Components::EntityGraphComponent{}};
        messageRelations.AddInsertChildInstruction(it->second.message);
        messageRelations.Commit();
    }
}

void NovelRT::Ecs::Scripting::UI::BranchTranslationSystem::UpdateContainers(Catalogue& catalogue)
{
    auto [branches, branchChoices, continues, graphComponents, transforms, uiButtons, uiClickEvents, uiElements, uiTexts, uiWidgetContainers] = catalogue.GetComponentViews<Components::Branch, Components::BranchChoice, Components::ContinueDecisionTree, NovelRT::Ecs::Components::EntityGraphComponent, NovelRT::Ecs::Components::TransformComponent, NovelRT::Ecs::UI::Components::UIButton, NovelRT::Ecs::UI::Components::UIClickEvent, NovelRT::Ecs::UI::Components::UIElement, NovelRT::Ecs::UI::Components::UIText, NovelRT::Ecs::UI::Components::UIWidgetContainer>();

    for (auto& [entity, info] : _activeTrees)
    {
        if (branches.HasComponent(entity))
        {
            auto branch = branches.GetComponent(entity);

            uiElements.PushComponentUpdateInstruction(info.messageContainer, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Container
            });

            uiElements.PushComponentUpdateInstruction(info.message, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Text
            });

            uiElements.PushComponentUpdateInstruction(info.choiceContainer, NovelRT::Ecs::UI::Components::UIElement {
                .Type = NovelRT::Ecs::UI::UIComponentType::Container
            });

            uiWidgetContainers.PushComponentUpdateInstruction(info.choiceContainer, NovelRT::Ecs::UI::Components::UIWidgetContainer {
                .title = new std::string("Choices")
            });

            uiWidgetContainers.PushComponentUpdateInstruction(info.messageContainer, NovelRT::Ecs::UI::Components::UIWidgetContainer {
                .title = new std::string("Prompt")
            });

            std::string prompt = *branch.prompt;
            uiTexts.PushComponentUpdateInstruction(info.message, NovelRT::Ecs::UI::Components::UIText {
                .textValue = new std::string(prompt),
                .colour = {255, 255, 255, 255}
            });

            if (info.choices.size() > branch.choices->size())
            {
                for (size_t i = branch.choices->size(); i < info.choices.size(); i++)
                {
                    catalogue.DeleteEntity(info.choices[i]);
                }

                info.choices.resize(branch.choices->size());
            }


            NovelRT::Ecs::EntityGraphView choiceRelations = graphComponents.HasComponent(info.choiceContainer)
                ? NovelRT::Ecs::EntityGraphView{catalogue, info.choiceContainer, graphComponents.GetComponent(info.choiceContainer)}
                : NovelRT::Ecs::EntityGraphView{catalogue, info.choiceContainer, NovelRT::Ecs::Components::EntityGraphComponent{}};
            for (size_t i = 0; i < info.choices.size(); i++)
            {
                uiElements.PushComponentUpdateInstruction(info.choices[i], NovelRT::Ecs::UI::Components::UIElement {
                    .Type = NovelRT::Ecs::UI::UIComponentType::Button
                });

                uiButtons.PushComponentUpdateInstruction(info.choices[i], NovelRT::Ecs::UI::Components::UIButton {
                    .label = new std::string(branch.choices->at(i)),
                    .eventId = i,
                    .bgColour = {0, 102, 204, 255},
                    .activeColour = {0, 82, 163, 255},
                    .hoveredColour = {0, 119, 255, 255},
                    .textColour = {255, 255, 255, 255},
                });

                //choiceRelations.AddInsertChildInstruction(info.choices[i]);
            }

            for (size_t i = info.choices.size(); i < branch.choices->size(); i++)
            {
                auto button = catalogue.CreateEntity();
                info.choices.push_back(button);

                uiElements.PushComponentUpdateInstruction(button, NovelRT::Ecs::UI::Components::UIElement {
                    .Type = NovelRT::Ecs::UI::UIComponentType::Button
                });

                std::string text = branch.choices->at(i);
                uiButtons.PushComponentUpdateInstruction(button, NovelRT::Ecs::UI::Components::UIButton {
                    .label = new std::string(text),
                    .eventId = i,
                    .bgColour = {0, 102, 204, 255},
                    .activeColour = {0, 82, 163, 255},
                    .hoveredColour = {0, 119, 255, 255},
                    .textColour = {255, 255, 255, 255},
                });

                transforms.PushComponentUpdateInstruction(button, NovelRT::Ecs::Components::TransformComponent{
                    .position = {20.0f, 20.0f + 35.0f * i},
                    .scale = {1240.0f, 30.0f},
                    .rotationInRadians = 0.0f
                });

                choiceRelations.AddInsertChildInstruction(button);
            }

            choiceRelations.Commit();
        }
        else
        {
            uiElements.RemoveComponent(info.messageContainer);
            uiElements.RemoveComponent(info.message);
            uiElements.RemoveComponent(info.choiceContainer);
            for (size_t i = 0; i < info.choices.size(); i++)
            {
                uiElements.RemoveComponent(info.choices[i]);
            }
        }

        for (size_t i = 0; i < info.choices.size(); i++)
        {
            if (uiClickEvents.HasComponent(info.choices[i]))
            {
                uiClickEvents.RemoveComponent(info.choices[i]);

                branchChoices.PushComponentUpdateInstruction(entity, Components::BranchChoice{ .choiceIndex = i });
                continues.PushComponentUpdateInstruction(entity, Components::ContinueDecisionTree{});
                break;
            }
        }
    }
}

NovelRT::Ecs::Scripting::UI::BranchTranslationSystem::BranchTranslationSystem()
{ }

void NovelRT::Ecs::Scripting::UI::BranchTranslationSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    CleanupInactiveTrees(catalogue);
    IdentifyNewTrees(catalogue);

    UpdateContainers(catalogue);
}
