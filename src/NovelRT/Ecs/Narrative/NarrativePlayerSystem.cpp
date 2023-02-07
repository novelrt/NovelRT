// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <iostream>

namespace NovelRT::Ecs::Narrative
{

    bool NarrativePlayerSystem::BeginPlay(ComponentView<RequestNarrativeScriptExecutionComponent>& requestView)
    {
        auto [entity, assetData] = *requestView.begin();

        auto&& storyStream = _resourceLoaderPluginProvider->GetResourceLoader()->GetStreamToAsset(assetData.narrativeScriptAssetId);

        std::cout << static_cast<void*>(storyStream.FileStream.get()) << std::endl;
        _storyInstance = _runtime.load_story(*storyStream.FileStream, "Placeholder String"); //throws here
        
        requestView.RemoveComponent(entity);

        fabulist::runtime::state::parameters params
        {
            sizeof(fabulist::runtime::state::parameters),
            [&](std::vector<std::string> choicesVector) 
            {
                auto [availableChoices, selectedChoice] = _catalogueForFrame->GetComponentViews<ChoiceMetadataComponent, SelectedChoiceComponent>();

                if (availableChoices.GetImmutableDataLength() == 0)
                {
                    _choiceMetadataLinkedListEntityId = _catalogueForFrame->CreateEntity();
                    LinkedEntityListView list(_choiceMetadataLinkedListEntityId.value(), _catalogueForFrame.value()); // we don't strictly need to make a list here but I'm futureproofing it for updates that are not in this version.

                    for(size_t index = 0; index < choicesVector.size(); index++)
                    {
                        EntityId newNode = _catalogueForFrame->CreateEntity();
                        availableChoices.AddComponent(newNode, ChoiceMetadataComponent{index});
                        list.AddInsertAtBackInstruction(newNode);
                    }

                    list.Commit();

                    return choicesVector.cend(); // there's no way the engine will see this modifcation until the next iteration, so we can just get out here.
                }

                if (selectedChoice.GetImmutableDataLength() == 0)
                {
                    return choicesVector.cend(); // user has not made a choice yet.
                }

                if (selectedChoice.GetImmutableDataLength() > 1)
                {
                    throw Exceptions::NotSupportedException("There can only be one selected choice in a given frame.");
                }

                auto [entity, choice] = *selectedChoice.begin();

                selectedChoice.RemoveComponent(entity);

                LinkedEntityListView list(_choiceMetadataLinkedListEntityId.value(), _catalogueForFrame.value()); // we don't strictly need to make a list here but I'm futureproofing it for updates that are not in this version.
                list.ClearAndAddRemoveNodeInstructionForAll();
                list.Commit();

                _choiceMetadataLinkedListEntityId.reset();

                return std::next(choicesVector.cbegin(), choice.choiceIndex);
            }
        };
        
        _storyInstanceState = _storyInstance->create_state(params, "root");
        return _storyInstanceState->update();
    }

    void NarrativePlayerSystem::DoNarrativeStoryCleanup(Catalogue& catalogue)
    {
        auto narrativeStoryStateComponents = catalogue.GetComponentView<NarrativeStoryStateComponent>();

        if (_narrativeStoryStateTrackerEntityId.has_value())
        {
            narrativeStoryStateComponents.RemoveComponent(_narrativeStoryStateTrackerEntityId.value());
            _narrativeStoryStateTrackerEntityId.reset();
        }

        _storyInstance.reset();
        _storyInstanceState.reset();

        if (_choiceMetadataLinkedListEntityId.has_value())
        {
            LinkedEntityListView(_choiceMetadataLinkedListEntityId.value(), catalogue).ClearAndAddRemoveNodeInstructionForAll();
            _choiceMetadataLinkedListEntityId.reset();
        }
    }

    NarrativePlayerSystem::NarrativePlayerSystem(
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceLoaderPluginProvider) noexcept
        : _runtime(), _resourceLoaderPluginProvider(resourceLoaderPluginProvider), _narrativeLoggingService()
    {

    }

    void NarrativePlayerSystem::Update(Timing::Timestamp /*delta*/, Catalogue catalogue)
    {
        auto [narrativeStoryStateComponents, scriptExecutionRequestComponents] =
            catalogue.GetComponentViews<NarrativeStoryStateComponent, RequestNarrativeScriptExecutionComponent>();

        size_t narrativeStoryStateCount = narrativeStoryStateComponents.GetImmutableDataLength();
        size_t scriptExecutionRequestCount = scriptExecutionRequestComponents.GetImmutableDataLength();

        if (narrativeStoryStateCount > 1 || scriptExecutionRequestCount > 1)
        {
            throw Exceptions::NotSupportedException();
        }

        if (narrativeStoryStateCount == 0)
        {
            if (scriptExecutionRequestCount == 1)
            {
                _narrativeStoryStateTrackerEntityId = catalogue.CreateEntity();
                narrativeStoryStateComponents.AddComponent(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
            }
            else
            {
                DoNarrativeStoryCleanup(catalogue);
            }

            return;
        }

        auto narrativeStoryStateComponent = narrativeStoryStateComponents.GetComponentUnsafe(_narrativeStoryStateTrackerEntityId.value());

        switch (narrativeStoryStateComponent.currentState)
        {
            default:
            case NarrativeStoryState::Idle:
            {
                if (scriptExecutionRequestCount == 0)
                {
                    break;
                }

                if (BeginPlay(scriptExecutionRequestComponents))
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
                }

                break;
            }
            case NarrativeStoryState::BeginPlay:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                break;
            }
            case NarrativeStoryState::Playing:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                auto state = _storyInstanceState->update();

                if (state->type() == "line")
                {
                    auto bla = static_cast<const fabulist::runtime::actions::line*>(**state);
                    _narrativeLoggingService.logInfo(bla->text());
                }
                else if (state->type() == "options")
                {
                    state->execute(_storyInstanceState.value());
                    break;
                }
                else
                {
                    state->execute(_storyInstanceState.value());
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::AwaitExecute});
                break;
            }
            case NarrativeStoryState::AwaitExecute:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                }

                break;
            }
            case NarrativeStoryState::ExecuteNext:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                if(_storyInstanceState->update())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                }
                else
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                }

                break;
            }
            case NarrativeStoryState::BeginStop:
            {
                _storyInstance.reset();
                _storyInstanceState.reset();
                
                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId.value(), NarrativeStoryStateComponent{NarrativeStoryState::Idle});
                
                if (_choiceMetadataLinkedListEntityId.has_value())
                {
                    LinkedEntityListView(_choiceMetadataLinkedListEntityId.value(), catalogue).ClearAndAddRemoveNodeInstructionForAll();
                    _choiceMetadataLinkedListEntityId.reset();
                }

                break;
            }
            case NarrativeStoryState::RequestDestroy:
            {
                DoNarrativeStoryCleanup(catalogue);
                break;
            }
        }
    }

    void NovelRT::Ecs::Narrative::NarrativePlayerSystem::RegisterCustomFunction(
        const std::string& name,
        fabulist::runtime::runtime::method_type function)
    {
        _runtime.register_method(name, function);
    }
}