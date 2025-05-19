// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATE_H
#define NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATE_H

#ifndef NOVELRT_ECS_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.Audio.h instead for the Ecs.Audio namespace subset.
#endif

namespace NovelRT::Ecs::Audio
{
    enum class AudioEmitterState : int32_t
    {
        Done = 0,
        ToPlay = 1,
        Playing = 2,
        ToStop = 3,
        Stopped = 4,
        ToPause = 5,
        Paused = 6,
        ToResume = 7,
        ToFadeIn = 8,
        FadingIn = 9,
        ToFadeOut = 10,
        FadingOut = 11
    };
}

#endif // NOVELRT_ECS_AUDIO_AUDIOEMITTERSTATE_H
