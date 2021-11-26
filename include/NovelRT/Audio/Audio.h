// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_H
#define NOVELRT_AUDIO_H

//Dependencies for Audio
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <vector>
#include <cstdint>
#include "../LoggingService.h"
#include "../Utilities/Lazy.h"
#include "../Utilities/Misc.h"
#include "../Exceptions/Exceptions.h"

#if defined(__cplusplus) && !defined(NOVELRT_C_API)
/***
 * @brief Contains audio features, such as playing audio, and managing audio resources.
 */
namespace NovelRT::Audio
{
    typedef std::vector<ALuint> SoundBank;
    typedef std::vector<ALuint> MusicBank;
    typedef class AudioService AudioService;
}
#endif

//Audio Types
#include "AudioService.h"

#endif // NOVELRT_AUDIO_H
