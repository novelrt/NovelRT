// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Narrative
{

    void NarrativePlayerSystem::BeginPlay(ComponentView<RequestNarrativeScriptExecutionComponent>& requestView)
    {
        unused(requestView);
        // this will process the GUID in the request component to get the correct script asset, and kick off the story.
    }

    NarrativePlayerSystem::NarrativePlayerSystem(
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceLoaderPluginProvider) noexcept
        : _runtime(),
          _resourceLoaderPluginProvider(resourceLoaderPluginProvider),
          _narrativeStoryStateTrackerEntityId(0)
    {
    }

    void NarrativePlayerSystem::Update(Timing::Timestamp delta, Catalogue catalogue)
    {
        unused(delta);
        auto [narrativeStoryStateComponents, scriptExecutionRequestComponents] =
            catalogue.GetComponentViews<NarrativeStoryStateComponent, RequestNarrativeScriptExecutionComponent>();

        size_t narrativeStoryStateCount = narrativeStoryStateComponents.GetImmutableDataLength();
        size_t scriptExecutionRequestCount = scriptExecutionRequestComponents.GetImmutableDataLength();

        if (narrativeStoryStateCount > 1 || scriptExecutionRequestCount > 1)
        {
            throw Exceptions::NotSupportedException();
        }

        if (narrativeStoryStateCount == 0 && scriptExecutionRequestCount == 1)
        {
            _narrativeStoryStateTrackerEntityId = catalogue.CreateEntity();
            narrativeStoryStateComponents.AddComponent(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
            BeginPlay(scriptExecutionRequestComponents);

            return;
        }

        auto narrativeStoryStateComponent = narrativeStoryStateComponents.GetComponentUnsafe(_narrativeStoryStateTrackerEntityId);

        switch (narrativeStoryStateComponent.currentState)
        {
            default:
            case NarrativeStoryState::Idle:
            {
                if (scriptExecutionRequestCount == 0)
                {
                    break;
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginPlay});
                BeginPlay(scriptExecutionRequestComponents);
                break;
            }
            case NarrativeStoryState::BeginPlay:
            {
                if (!_storyInstance.has_value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                break;
            }
            case NarrativeStoryState::Playing:
            {
                if (!_storyInstance.has_value() || !_lastUpdatedState.value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                if (_lastUpdatedState.value()->type() == "line")
                {
                    // render here, right now we can't render so this is blank
                }
                else
                {
                    _lastUpdatedState.value()->execute(_storyInstanceState.value());
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::AwaitExecute});
                break;
            }
            case NarrativeStoryState::AwaitExecute:
            {
                if (!_storyInstance.has_value() || !_lastUpdatedState.value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                }

                break;
            }
            case NarrativeStoryState::ExecuteNext:
            {
                if (!_storyInstance.has_value() || !_lastUpdatedState.value())
                {
                    narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::BeginStop});
                    break;
                }

                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::Playing});
                break;
            }
            case NarrativeStoryState::BeginStop:
            {
                _storyInstance.reset();
                _storyInstanceState.reset();
                _lastUpdatedState.reset();
                
                narrativeStoryStateComponents.PushComponentUpdateInstruction(_narrativeStoryStateTrackerEntityId, NarrativeStoryStateComponent{NarrativeStoryState::Idle});
                break;
            }
        }
    }
}