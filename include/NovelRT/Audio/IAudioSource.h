// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_IAUDIOSOURCE_H
#define NOVELRT_AUDIO_IAUDIOSOURCE_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    class IAudioSource
    {
    public:
        SourceState state = SourceState::Initialise;
        std::string soundName;
        float volumeIndB = 0.0f;
        float soundVolume = 0.0f;
        bool stopRequested = false;

        virtual void Update(float delta);
        virtual bool IsPlaying() const;
        virtual float GetdBVolume() const;
    };
}

#endif // NOVELRT_AUDIO_IAUDIOSOURCE_H
