// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NARRATIVEPLAYERSTATE_H
#define NOVELRT_NARRATIVEPLAYERSTATE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    enum class NarrativeStoryState : uint32_t
    {
        Idle = 0,
        BeginPlay = 1,
        Playing = 2,
        AwaitExecute = 3,
        ExecuteNext = 4,
        BeginStop = 5,
        RequestDestroy = 6
    };
}

#endif // NOVELRT_NARRATIVEPLAYERSTATE_H