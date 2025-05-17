// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <cstdint>

namespace NovelRT::Audio
{
    enum class AudioSourceState: int32_t
    {
        SOURCE_STOPPED = 0,
        SOURCE_PAUSED = 1,
        SOURCE_PLAYING = 2
    };
}
