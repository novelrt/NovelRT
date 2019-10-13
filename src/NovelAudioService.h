// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELAUDIOSERVICE_H
#define NOVELRT_NOVELAUDIOSERVICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

namespace NovelRT {
class NovelAudioService {

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

  int convertToMixVolume(float value);
  std::string findByChannelMap(int channel);
  void incrementNextChannel();
public:
  bool isInitialized;

  NovelAudioService();
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
  ~NovelAudioService();
};
}

#endif
