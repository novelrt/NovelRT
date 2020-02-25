// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_AUDIOSERVICE_H
#define NOVELRT_AUDIOSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

//TODO: This won't exist after Kenny's rewrite, not too bothered about this class.
namespace NovelRT::Audio {
  class AudioService {
  private:
    const size_t _bufferSize = 2048;
    const ALuint _noBuffer = 0;
    const ALfloat _pitch = 1.0f;

    std::vector<ALuint> _soundStorage;
    Utilities::Lazy<std::unique_ptr<ALCdevice, void(*)(ALCdevice*)>> _device;
    Utilities::Lazy<std::unique_ptr<ALCcontext, void(*)(ALCcontext*)>> _context;
    LoggingService _logger;
    ALuint _musicSource;
    ALint _musicSourceState;
    ALint _musicLoopAmount;
    ALint _soundSourceState;
    ALint _soundLoopAmount;
    SoundBank _sounds;
    MusicBank _music;
    std::string _deviceName;
    bool _manualLoad;

    ALuint readFile(std::string input);
    std::string getALError();

  public:
    bool isInitialised;

    AudioService();
    ~AudioService();

    bool initializeAudio();
    std::vector<ALuint>::iterator loadMusic(std::string input);
    
    void unloadMusic(ALuint handle);
    void setSoundVolume(ALuint source, float val);
    void setSoundPosition(ALuint source, float posX, float posY);
    void resumeMusic();
    void playMusic(std::vector<ALuint>::iterator handle, int loops);
    void pauseMusic();
    void stopMusic();
    void setMusicVolume(float value);
    void checkSources();

    //For touhou sample
    //Returns source
    ALuint loadSound(std::string input);
    void unloadSound(ALuint handle);
    void playSound(ALuint handle, int loops);
    void stopSound(ALuint handle);


  };
}

#endif
