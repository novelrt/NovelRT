// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_SOUDNDEFINITION_H
#define NOVELRT_AUDIO_SOUDNDEFINITION_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    struct SoundDefinition
    {
        std::string soundName;
        std::string soundFileName;
        float defaultVolumeIndB;
        bool looping;
    };
}

#endif // NOVELRT_AUDIO_SOUDNDEFINITION_H
