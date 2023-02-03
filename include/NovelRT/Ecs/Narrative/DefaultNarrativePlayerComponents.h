// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H
#define NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    struct NarrativeStoryStateComponent
    {
        NarrativeStoryState currentState = NarrativeStoryState::Idle;

        inline NarrativeStoryStateComponent& operator+=(const NarrativeStoryStateComponent& other)
        {
            currentState = other.currentState;
            return *this;
        }

        inline bool operator==(const NarrativeStoryStateComponent& other) const noexcept
        {
            return currentState == other.currentState;
        }

        inline bool operator!=(const NarrativeStoryStateComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    struct RequestNarrativeScriptExecutionComponent
    {
        uuids::uuid narrativeScriptAssetId = uuids::uuid();
    };
}

#endif // NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H