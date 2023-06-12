// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_NARRATIVE_H
#define NOVELRT_ECS_NARRATIVE_H

#include "../Ecs.h"

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

// Ecs::Narrative Dependencies
#include <fabulist/runtime/action.hpp>
#include <fabulist/runtime/actions/action.hpp>
#include <fabulist/runtime/actions/line.hpp>
#include <fabulist/runtime/decoder.hpp>
#include <fabulist/runtime/runtime.hpp>
#include <fabulist/runtime/section.hpp>
#include <fabulist/runtime/state.hpp>
#include <fabulist/runtime/story.hpp>
#include <fabulist/runtime/version.hpp>

namespace NovelRT::Ecs::Narrative
{
    enum class NarrativeStoryState : uint32_t;
    struct NarrativeStoryStateComponent;
    class NarrativePlayerSystem;
    struct RequestNarrativeScriptExecutionComponent;
    struct ChoiceMetadataComponent;
    struct SelectedChoiceComponent;
}

// clang-format off
#include "NarrativeStoryState.h"
#include "DefaultNarrativePlayerComponents.h"
#include "NarrativePlayerSystem.h"
// clang-format on

#endif
