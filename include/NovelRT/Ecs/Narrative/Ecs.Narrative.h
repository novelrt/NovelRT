// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_NARRATIVE_H
#define NOVELRT_ECS_NARRATIVE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    enum class NarrativePlayerState : uint32_t;
    struct NarrativePlayerStateComponent;
    class NarrativePlayerSystem;
    class CharacterInformation;
}

// clang-format off
#include "NarrativePlayerState.h"
#include "DefaultNarrativeComponentTypes.h"
#include "NarrativePlayerSystem.h"
#include "CharacterInformation.h"
// clang-format on

#endif // NOVELRT_ECS_NARRATIVE_H
