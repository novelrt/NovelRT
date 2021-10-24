// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
#define NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H

namespace NovelRT::Ecs::Audio
{
    struct AudioEmitterStateComponent
    {
        AudioEmitterState state = AudioEmitterState::Stopped;

        inline AudioEmitterStateComponent& operator+=(const AudioEmitterStateComponent& other) noexcept
        {
            state = other.state;
            return *this;
        };
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATECOMPONENT_H
