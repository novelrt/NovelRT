// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_ISOUND_HPP
#define NOVELRT_AUDIO_ISOUND_HPP

namespace NovelRT::Audio
{
    struct ISound : public IAudioObject
    {
        bool looping;
        float decibelVolume;
        virtual ~ISound();
    };
}

#endif // NOVELRT_AUDIO_ISOUND_HPP
