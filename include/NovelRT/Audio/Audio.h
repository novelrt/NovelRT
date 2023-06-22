// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_H
#define NOVELRT_AUDIO_H

// Dependencies for Audio
#include <cstdint>
#include <map>
#include <string>

/***
 * @brief Contains audio interfaces for usage, such as the NovelRT Audio Engine and Audio Sources.
 */
namespace NovelRT::Audio
{
    enum class SourceState : uint32_t;
    class IAudioSource;
    struct SoundDefinition;
    typedef std::map<uint32_t, IAudioSource> SourceMap;
    typedef std::map<std::string, SoundDefinition> SoundMap;
    class IAudioEngine;
}

// Audio Types
#include "SourceState.h"
#include "IAudioSource.h"
#include "SoundDefinition.h"
#include "IAudioEngine.h"

#endif // NOVELRT_AUDIO_H
