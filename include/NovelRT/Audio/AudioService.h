// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_AUDIOSERVICE_H
#define NOVELRT_AUDIO_AUDIOSERVICE_H

#ifndef NOVELRT_AUDIO_H
#error NovelRT does not support including types explicitly by default. Please include Audio.h instead for the Audio namespace subset.
#endif

namespace NovelRT::Audio
{
    // TODO: This won't exist after Kenny's rewrite, not too bothered about this class.
    class AudioService
    {
    private:
        const ALuint _noBuffer = 0;
        const ALfloat _pitch = 1.0f;

        Utilities::Lazy<std::unique_ptr<ALCdevice, void (*)(ALCdevice*)>> _device;
        Utilities::Lazy<std::unique_ptr<ALCcontext, void (*)(ALCcontext*)>> _context;
        std::string _deviceName;
        LoggingService _logger;
        bool _manualLoad;
        MusicBank _music;
        ALuint _musicSource;
        ALint _musicSourceState;
        bool _musicStopRequested;
        ALint _musicLoopAmount;
        ALint _soundLoopAmount;
        ALint _soundSourceState;
        SoundBank _soundStorage;
        SoundBank _bufferStorage;

        ALuint BufferAudioFrameData(gsl::span<const int16_t> audioFrameData, int32_t channelCount, int32_t sampleRate);
        std::string GetALError();

    public:
        bool isInitialised;

        AudioService();
        ~AudioService();

        bool InitializeAudio();
        std::vector<ALuint>::iterator LoadMusic(gsl::span<const int16_t> audioFrameData,
                                                int32_t channelCount,
                                                int32_t sampleRate);

        void SetSoundVolume(ALuint source, float val);
        void SetSoundPosition(ALuint source, float posX, float posY);
        void ResumeMusic();
        void PlayMusic(std::vector<ALuint>::iterator handle, int32_t loops);
        void PauseMusic();
        void StopMusic();
        void SetMusicVolume(float value);
        void CheckSources();
        ALuint LoadSound(gsl::span<const int16_t> audioFrameData, int32_t channelCount, int32_t sampleRate);
        void Unload(ALuint handle);
        void PlaySound(ALuint handle, int32_t loops);
        void StopSound(ALuint handle);
        void TearDown();
        [[nodiscard]] bool IsLoaded(std::vector<ALuint>::iterator handle);
        [[nodiscard]] bool IsLoaded(ALuint handle);
        [[nodiscard]] bool IsMusicPlaying();
        [[nodiscard]] bool IsSoundPlaying(ALuint handle);
        [[nodiscard]] float GetMusicVolume();
        [[nodiscard]] float GetSoundVolume(ALuint handle);
    };
}

#endif // NOVELRT_AUDIO_AUDIOSERVICE_H
