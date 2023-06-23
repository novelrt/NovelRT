// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_XAUDIO2_H
#define NOVELRT_AUDIO_XAUDIO2_H

#include "../Audio.h"

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

// Dependencies for Audio
#include "../../Exceptions/Exceptions.h"
#include "../../Utilities/Misc.h"
#include "../../ResourceManagement/Windows/ResourceManagement.Desktop.h"
#include <memory>
#include <comdef.h>
#include <xaudio2.h>

/***
 * @brief Contains the Windows implementation of NovelRT's Audio types.
 */
namespace NovelRT::Audio::XAudio2
{
    //class XAudio2Source;
    class XAudio2Engine;
}

#include "XAudio2Engine.h"


#endif // NOVELRT_AUDIO_XAUDIO2_H
