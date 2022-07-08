// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H
#define NOVELRT_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H

#ifndef NOVELRT_ECS_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.Audio.h instead for the Ecs.Audio namespace subset.
#endif

namespace NovelRT::Ecs::Audio
{
    struct AudioEmitterComponent
    {
        uint32_t handle;
        bool isMusic;
        int32_t numberOfLoops;
        float volume;

        inline AudioEmitterComponent& operator+=(const AudioEmitterComponent& other) noexcept
        {
            bool handleChanged = (handle == other.handle);
            handle = handleChanged ? other.handle : handle;
            // isMusic should never change otherwise the component may be being abused.
            numberOfLoops = handleChanged ? other.numberOfLoops : numberOfLoops;
            volume = handleChanged ? other.volume : volume + other.volume;
            return *this;
        };
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOEMITTERCOMPONENT_H
