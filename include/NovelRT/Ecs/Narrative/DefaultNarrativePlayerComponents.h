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
        bool shouldDestroy = false;

        inline NarrativeStoryStateComponent& operator+=(const NarrativeStoryStateComponent& other) noexcept
        {
            currentState = other.currentState;
            shouldDestroy = other.shouldDestroy;
            return *this;
        }

        inline bool operator==(const NarrativeStoryStateComponent& other) const noexcept
        {
            return currentState == other.currentState && shouldDestroy == other.shouldDestroy;
        }

        inline bool operator!=(const NarrativeStoryStateComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    struct RequestNarrativeScriptExecutionComponent
    {
        uuids::uuid narrativeScriptAssetId = uuids::uuid();
        bool shouldDestroy = false;

        inline RequestNarrativeScriptExecutionComponent& operator+=(
            const RequestNarrativeScriptExecutionComponent& other) noexcept
        {
            narrativeScriptAssetId = other.narrativeScriptAssetId;
            shouldDestroy = other.shouldDestroy;
            return *this;
        }

        inline bool operator==(const RequestNarrativeScriptExecutionComponent& other) const noexcept
        {
            return narrativeScriptAssetId == other.narrativeScriptAssetId && shouldDestroy == other.shouldDestroy;
        }

        inline bool operator!=(const RequestNarrativeScriptExecutionComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    struct ChoiceMetadataComponent
    {
        size_t choiceIndex = 0;
        bool shouldDestroy = false;

        inline ChoiceMetadataComponent& operator+=(const ChoiceMetadataComponent& other) noexcept
        {
            choiceIndex = other.choiceIndex;
            shouldDestroy = other.shouldDestroy;
            return *this;
        }

        inline bool operator==(const ChoiceMetadataComponent& other) const noexcept
        {
            return choiceIndex == other.choiceIndex && shouldDestroy == other.shouldDestroy;
        }

        inline bool operator!=(const ChoiceMetadataComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };

    struct SelectedChoiceComponent
    {
        size_t choiceIndex = 0;
        bool shouldDestroy = false;

        inline SelectedChoiceComponent& operator+=(const SelectedChoiceComponent& other) noexcept
        {
            choiceIndex = other.choiceIndex;
            return *this;
        }

        inline bool operator==(const SelectedChoiceComponent& other) const noexcept
        {
            return choiceIndex == other.choiceIndex && shouldDestroy == other.shouldDestroy;
        }

        inline bool operator!=(const SelectedChoiceComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };
}

#endif // NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H