// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
#define NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H

#ifndef NOVELRT_ECS_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.Audio.h instead for the Ecs.Audio namespace subset.
#endif

namespace NovelRT::Ecs::Audio
{
    struct AudioEmitterStateComponent
    {
        AudioEmitterState state = AudioEmitterState::Stopped;
        float fadeDuration = 0;
        float fadeExpectedVolume = 0;

        inline AudioEmitterStateComponent& operator+=(const AudioEmitterStateComponent& other) noexcept
        {
            state = other.state;
            fadeDuration = other.fadeDuration;
            fadeExpectedVolume = other.fadeExpectedVolume;
            return *this;
        };
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
