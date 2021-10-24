// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_AUDIO_EMITTERSTATE_H
#define NOVELRT_ECS_AUDIO_EMITTERSTATE_H

namespace NovelRT::Ecs::Audio
{
    enum class EmitterState : int32_t
    {
        Done = 0,
        ToPlay = 1,
        Playing = 2,
        ToStop = 3,
        Stopped = 4,
        ToPause = 5,
        Paused = 6,
        ToResume = 7
    };
}

#endif // NOVELRT_ECS_AUDIO_EMITTERSTATE_H
