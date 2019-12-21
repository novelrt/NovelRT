// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_AUDIOSERVICE_H
#define NOVELRT_AUDIOSERVICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
#include <typeinfo>
#include "../LoggingService.h"

namespace NovelRT::Audio {
  class AudioService {

    typedef std::map<std::string, Mix_Chunk*> SoundBank;
    typedef std::map<std::string, Mix_Music*> MusicBank;
    typedef std::map<std::string, int> ChannelMap;

  private:
    int _nextChannel;
    int _musicTime;
    int _musicPausedTime;
    const int NOVEL_MIXER_CHANNELS = 2;
    const int MIXER_TRUE = 1;
    const int MIXER_INFINITE_LOOP = -1;
    const int MIXER_NO_LOOP = 0;
    const int MIXER_NO_EXPLICIT_CHANNEL = -1;
    const int NOVEL_MUSIC_CHANNEL = -3;
    SoundBank _sounds;
    MusicBank _music;
    ChannelMap _channelMap;
    NovelLoggingService _logger;

    int convertToMixVolume(float value);
    std::string findByChannelMap(int channel);
    std::string getSDLError();
    void incrementNextChannel();
    void logIfSDLFailure(std::function<int(Uint32)> sdlFunction, Uint32 sdlFlag);
    void logIfMixerFailure(std::function<int(int)> mixerFunction, int mixerFlag);
    void logIfMixerFailure(std::function<int(int,Uint16,int,int)> mixerFunction, int freq, Uint16 mixerFormat, int channels, int sampleSize);
  public:
    bool isInitialized;

    AudioService();
    ~AudioService();

    bool initializeAudio();
    void load(std::string input, bool isMusic);
    void unload(std::string input, bool isMusic);
    void playSound(std::string soundName, int loops);
    void stopSound(std::string soundName);
    void setSoundVolume(std::string soundName, float val);
    void setSoundPosition(std::string soundName, int angle, int distance);
    void setSoundDistance(std::string soundName, int distance);
    void setSoundPanning(std::string soundName, int leftChannel, int rightChannel);
    void resumeMusic();
    void playMusic(std::string musicName, int loops);
    void pauseMusic();
    void stopMusic();
    void setMusicVolume(float value);
    void fadeMusicInOnce(std::string musicName, int ms);
    void fadeMusicIn(std::string musicName, int loops, int ms);
    void fadeMusicOut(int ms);
    void setGlobalVolume(float value);
  };
}

#endif
