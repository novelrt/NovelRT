// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H
#define NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    // I couldn't think of any other component types we might need, so for now this is all we got. - Matt
    struct NarrativePlayerStateComponent
    {
        NarrativePlayerState currentState = NarrativePlayerState::Idle;
        Atom sectionId = 0;
        Atom characterId = 0;

        inline NarrativePlayerStateComponent& operator+=(const NarrativePlayerStateComponent& other)
        {
            currentState = other.currentState;
            sectionId = other.sectionId;
            characterId = other.characterId;
        }

        inline bool operator==(const NarrativePlayerStateComponent& other) const noexcept
        {
            return currentState == other.currentState && sectionId == other.sectionId && characterId == other.characterId;
        }

        inline bool operator!=(const NarrativePlayerStateComponent& other) const noexcept
        {
            return !(*this == other);
        }
    };
}

#endif // NOVELRT_ECS_NARRATIVE_DEFAULTNARRATIVECOMPONENTTYPES_H
