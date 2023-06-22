// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_SOURCESTATE_H
#define NOVELRT_AUDIO_SOURCESTATE_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    enum class SourceState : uint32_t
    {
        Initialise = 0,
        ToPlay = 1,
        Loading = 2,
        Playing = 3,
        Stopping = 4,
        Stopped = 5
    };
}

#endif // !NOVELRT_AUDIO_SOURCESTATE_H
