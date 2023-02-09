// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Narrative
{

    bool NarrativePlayerSystem::BeginPlay(ComponentView<RequestNarrativeScriptExecutionComponent>& requestView)
    {
        auto [entity, assetData] = *requestView.begin();

        auto scriptAsset =
            _resourceLoaderPluginProvider->GetResourceLoader()->GetStreamToAsset(assetData.narrativeScriptAssetId);

        _storyInstance = _runtime.load_story(*scriptAsset.FileStream.get(),
                                             uuids::to_string(scriptAsset.DatabaseHandle)); // throws here

        requestView.RemoveComponent(entity);

        fabulist::runtime::state::parameters params{
            sizeof(fabulist::runtime::state::parameters), [&](const std::vector<std::string>& choicesVector) {
                auto [availableChoices, selectedChoice] =
                    _catalogueForFrame->GetComponentViews<ChoiceMetadataComponent, SelectedChoiceComponent>();

                if (availableChoices.GetImmutableDataLength() == 0)
                {
                    _choiceMetadataLinkedListEntityId = _catalogueForFrame->CreateEntity();
                    LinkedEntityListView list(
                        _choiceMetadataLinkedListEntityId.value(),
                        _catalogueForFrame.value()); // we don't strictly need to make a list here but I'm
                                                     // futureproofing it for updates that are not in this version.

                    for (size_t index = 0; index < choicesVector.size(); index++)
                    {
                        EntityId newNode = _catalogueForFrame->CreateEntity();
                        availableChoices.AddComponent(newNode, ChoiceMetadataComponent{index});
                        list.AddInsertAtBackInstruction(newNode);
                    }

                    list.Commit();

                    return choicesVector.cend(); // there's no way the engine will see this modifcation until the next
                                                 // iteration, so we can just get out here.
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

                LinkedEntityListView list(
                    _choiceMetadataLinkedListEntityId.value(),
                    _catalogueForFrame.value()); // we don't strictly need to make a list here but I'm futureproofing it
                                                 // for updates that are not in this version.

                for (EntityId node : list)
                {
                    availableChoices.RemoveComponent(node);
                }

                list.ClearAndAddRemoveNodeInstructionForAll();
                list.Commit();

                _choiceMetadataLinkedListEntityId.reset();
                _optionSelected = true;
                return std::next(choicesVector.cbegin(), choice.choiceIndex);
            }};

        _storyInstanceState = _storyInstance->create_state(params, "root");
        return _storyInstanceState->update();
    }

    void NarrativePlayerSystem::DoNarrativeStoryCleanup()
    {
        auto narrativeStoryStateComponents = _catalogueForFrame->GetComponentView<NarrativeStoryStateComponent>();

        if (_narrativeStoryStateTrackerEntityId.has_value())
        {
            narrativeStoryStateComponents.RemoveComponent(_narrativeStoryStateTrackerEntityId.value());
            _narrativeStoryStateTrackerEntityId.reset();
        }

        _storyInstance.reset();
        _storyInstanceState.reset();

        if (_choiceMetadataLinkedListEntityId.has_value())
        {
            auto [availableChoicesComponents, selectedChoiceComponents] =
                _catalogueForFrame->GetComponentViews<ChoiceMetadataComponent, SelectedChoiceComponent>();
            LinkedEntityListView list(_choiceMetadataLinkedListEntityId.value(), _catalogueForFrame.value());

            for (EntityId node : list)
            {
                availableChoicesComponents.RemoveComponent(node);
            }

            for (auto&& [entity, choice] : selectedChoiceComponents)
            {
                selectedChoiceComponents.RemoveComponent(entity);
            }

            _choiceMetadataLinkedListEntityId.reset();
        }
    }

    NarrativePlayerSystem::NarrativePlayerSystem(
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceLoaderPluginProvider) noexcept
        : _runtime(),
          _resourceLoaderPluginProvider(resourceLoaderPluginProvider),
          _narrativeLoggingService(),
          _optionSelected(false)
    {
        fabulist::runtime::register_default_actions(_runtime);
    }

    void NarrativePlayerSystem::Update(Timing::Timestamp /*delta*/, Catalogue catalogue)
    {
        _catalogueForFrame.emplace(catalogue);
        auto [narrativeStoryStateComponents, scriptExecutionRequestComponents] =
            _catalogueForFrame
                ->GetComponentViews<NarrativeStoryStateComponent, RequestNarrativeScriptExecutionComponent>();

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
                _narrativeStoryStateTrackerEntityId = _catalogueForFrame->CreateEntity();

                if (BeginPlay(scriptExecutionRequestComponents))
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
                }
            }
            else
            {
                DoNarrativeStoryCleanup();
            }

            return;
        }

        auto narrativeStoryStateComponent =
            narrativeStoryStateComponents.GetComponentUnsafe(_narrativeStoryStateTrackerEntityId.value());

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
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
                }

                break;
            }
            case NarrativeStoryState::BeginPlay:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(
                    _narrativeStoryStateTrackerEntityId.value(),
                    NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                break;
            }
            case NarrativeStoryState::Playing:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                auto state = _storyInstanceState->update();

                if (state->type() == "line")
                {
                    auto bla = static_cast<const fabulist::runtime::actions::line*>(**state);

                    _narrativeLoggingService.logInfo("[Char: {}] {}", bla->speaker(), bla->text());
                }
                else if (state->type() == "options")
                {
                    state->execute(_storyInstanceState.value());
                    if (_optionSelected)
                    {
                        if (_storyInstanceState->update())
                        {
                            _optionSelected = false;
                            auto availableChoices = _catalogueForFrame->GetComponentView<ChoiceMetadataComponent>();
                            for (auto&& [entity, choice] : availableChoices)
                            {
                                availableChoices.RemoveComponent(entity);
                            }
                        }
                    }
                    break;
                }
                else
                {
                    state->execute(_storyInstanceState.value());
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(
                    _narrativeStoryStateTrackerEntityId.value(),
                    NarrativeStoryStateComponent{NarrativeStoryState::AwaitExecute});
                break;
            }
            case NarrativeStoryState::AwaitExecute:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                }

                break;
            }
            case NarrativeStoryState::ExecuteNext:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                if (_storyInstanceState->update())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                }
                else
                {
                    // Assume we hit end of story and begin to stop.
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(
                        _narrativeStoryStateTrackerEntityId.value(),
                        NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                }

                break;
            }
            case NarrativeStoryState::BeginStop:
            {
                _storyInstance.reset();
                _storyInstanceState.reset();

                narrativeStoryStateComponents.PushComponentUpdateInstruction(
                    _narrativeStoryStateTrackerEntityId.value(),
                    NarrativeStoryStateComponent{NarrativeStoryState::Idle});

                if (_choiceMetadataLinkedListEntityId.has_value())
                {
                    LinkedEntityListView(_choiceMetadataLinkedListEntityId.value(), _catalogueForFrame.value())
                        .ClearAndAddRemoveNodeInstructionForAll();
                    _choiceMetadataLinkedListEntityId.reset();
                }

                break;
            }
            case NarrativeStoryState::RequestDestroy:
            {
                DoNarrativeStoryCleanup();
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
