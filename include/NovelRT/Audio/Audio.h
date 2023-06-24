// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_H
#define NOVELRT_AUDIO_H

// Dependencies for Audio
#include <cstdint>
#include <map>
#include <string>
#include "../LoggingService.h"
#include "../ResourceManagement/ResourceManagement.h"

/***
 * @brief Contains audio interfaces for usage, such as the NovelRT Audio Engine and Audio Sources.
 */
namespace NovelRT::Audio
{
    enum class SourceState : uint32_t;
    class IAudioSource;
    struct SoundDefinition;
    class IAudioEngine;
}

// Audio Types
#include "SourceState.h"
#include "IAudioSource.h"
#include "SoundDefinition.h"
#include "IAudioEngine.h"

#endif // NOVELRT_AUDIO_H
