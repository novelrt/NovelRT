// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_IAUDIOENGINE_H
#define NOVELRT_AUDIO_IAUDIOENGINE_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    class IAudioEngine
    {
    // protected:
    //     SoundMap _sounds;
    //     SourceMap _sources;

    public:
        virtual void Initialise() = 0;
        virtual void Update() = 0;
        virtual void TearDown() = 0;

        virtual void LoadSound(const SoundDefinition& sound) = 0;
        virtual void UnloadSound(const std::string& soundName) = 0;
        virtual uint32_t PlaySound(const std::string& soundName, float volumeIndB) = 0;
        virtual void StopSource(uint32_t sourceId) = 0;
        virtual void PauseSource(uint32_t sourceId) = 0;
        virtual void SetSourceVolume(uint32_t sourceId, float volumeIndB) = 0;
        virtual bool IsPlaying(uint32_t sourceId) = 0;
    };
}

#endif // NOVELRT_AUDIO_IAUDIOENGINE_H
