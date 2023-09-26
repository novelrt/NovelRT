// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_H
#define NOVELRT_AUDIO_H

// Dependencies for Audio
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/LoggingService.h>
#include <NovelRT/Utilities/Lazy.h>
#include <NovelRT/Utilities/Misc.h>
#include <NovelRT/Maths/Maths.h>
//#include <AL/al.h>
//#include <AL/alc.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <map>

/***
 * @brief Contains audio features, such as playing audio, and managing audio resources.
 */
namespace NovelRT::Audio
{
    typedef struct IAudioObject IAudioObject;
    typedef struct IAudioImpl IAudioImpl;
    typedef struct IAudioListener IAudioListener;
    typedef struct ISound ISound;
    typedef class AudioEngine AudioEngine;
    //typedef class AudioService AudioService;
}

// Audio Types
#include <NovelRT/Audio/IAudioObject.hpp>
#include <NovelRT/Audio/IAudioListener.hpp>
#include <NovelRT/Audio/IAudioImpl.hpp>
#include <NovelRT/Audio/ISound.hpp>
#include <NovelRT/Audio/AudioEngine.hpp>

#endif // NOVELRT_AUDIO_H
