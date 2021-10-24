// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_H
#define NOVELRT_ECS_AUDIO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

#include <map>
#include "../../Audio/Audio.h"

namespace NovelRT::Ecs::Audio
{
    enum class EmitterState : int32_t;
    struct AudioEmitterComponent;
    class AudioSystem;
}

#include "EmitterState.h"
#include "AudioEmitterComponent.h"
#include "AudioSystem.h"

#endif // NOVELRT_ECS_AUDIO_H