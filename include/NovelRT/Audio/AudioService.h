// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIOSERVICE_H
#define NOVELRT_AUDIOSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Audio
{
    // TODO: This won't exist after Kenny's rewrite, not too bothered about this class.
    class AudioService
    {
      private:
        const size_t _bufferSize = 2048;
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
        ALint _musicLoopAmount;
        ALint _soundLoopAmount;
        ALint _soundSourceState;
        SoundBank _soundStorage;
        SoundBank _bufferStorage;

        ALuint readFile(std::string input);
        std::string getALError();

      public:
        bool isInitialised;

        AudioService();
        ~AudioService();

        bool initializeAudio();
        std::vector<ALuint>::iterator loadMusic(std::string input);

        void setSoundVolume(ALuint source, float val);
        void setSoundPosition(ALuint source, float posX, float posY);
        void resumeMusic();
        void playMusic(std::vector<ALuint>::iterator handle, int32_t loops);
        void pauseMusic();
        void stopMusic();
        void setMusicVolume(float value);
        void checkSources();
        ALuint loadSound(std::string input);
        void unload(ALuint handle);
        void playSound(ALuint handle, int32_t loops);
        void stopSound(ALuint handle);
        void tearDown();
    };
} // namespace NovelRT::Audio

#endif
