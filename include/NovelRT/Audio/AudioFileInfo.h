// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_AUDIOFILEINFO_H
#define NOVELRT_AUDIO_AUDIOFILEINFO_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    struct AudioFileInfo
    {
        int32_t channels;
        int32_t frequency;
        size_t size;
        void* data;
    };
}

#endif // NOVELRT_AUDIO_AUDIOFILEINFO_H
