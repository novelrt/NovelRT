// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_H
#define NOVELRT_ECS_AUDIO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

#include <NovelRT/Timing/StepTimer.h>
#include <NovelRT/Timing/Timestamp.h>
#include <NovelRT/Audio/AudioMixer.hpp>
#include <NovelRT/Audio/AudioSourceState.hpp>

#include <chrono>
#include <map>

namespace NovelRT::Ecs::Audio
{
    enum class AudioEmitterState : int32_t;
    struct AudioEmitterComponent;
    class AudioSystem;
}

#include "AudioEmitterComponent.h"
#include "AudioEmitterState.h"
#include "AudioEmitterStateComponent.h"
#include "AudioSystem.h"

#endif // NOVELRT_ECS_AUDIO_H
