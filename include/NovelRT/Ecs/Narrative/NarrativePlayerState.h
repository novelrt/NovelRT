// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NARRATIVEPLAYERSTATE_H
#define NOVELRT_NARRATIVEPLAYERSTATE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    enum class NarrativePlayerState : uint32_t
    {
        Idle = 0,
        RequestPlay = 1,
        Playing = 2,
        RequestStop = 3,
        RequestDestroy = 4
    };
}

#endif // NOVELRT_NARRATIVEPLAYERSTATE_H
