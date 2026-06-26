#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Audio
{
    enum class AudioSourceState : int32_t
    {
        SourceStopped = 0,
        SourcePaused = 1,
        SourcePlaying = 2
    };
}
