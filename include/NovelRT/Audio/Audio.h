// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_H
#define NOVELRT_AUDIO_H

// Dependencies for Audio
#include "../Exceptions/Exceptions.h"
#include "../LoggingService.h"
#include "../Utilities/Lazy.h"
#include "../Utilities/Misc.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <cstdint>
#include <fstream>
#include <vector>

/***
 * @brief Contains audio features, such as playing audio, and managing audio resources.
 */
namespace NovelRT::Audio
{
    struct AudioFileInfo;
    typedef std::vector<ALuint> SoundBank;
    typedef std::vector<ALuint> MusicBank;
    typedef class AudioService AudioService;
}

// Audio Types
#include "AudioFileInfo.h"
#include "AudioService.h"

#endif // NOVELRT_AUDIO_H
