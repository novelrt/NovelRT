// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Audio {
AudioService::AudioService() : _device(Utilities::Lazy<std::unique_ptr<ALCdevice, void(*)(ALCdevice*)>> (std::function<ALCdevice*()>([this] {
    auto device = alcOpenDevice((_deviceName.empty())? nullptr : _deviceName.c_str());
    if (!device) {
      throw std::runtime_error("OpenAL: Could not get audio devices!");
    }
    return device;
  }), [](auto x) { alcCloseDevice(x); })),
  _context(Utilities::Lazy<std::unique_ptr<ALCcontext, void(*)(ALCcontext*)>>(std::function<ALCcontext*()>([this] {
    auto context = alcCreateContext(_device.getActual(), nullptr);
    alcMakeContextCurrent(context);
    isInitialised = true;
    _deviceName = alcGetString(_device.getActual(), ALC_DEVICE_SPECIFIER);
    _logger.logInfo("OpenAL Initialized on device: ", _deviceName);
    return context;
  }), [](auto x) {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(x);
  })), isInitialised(false), _logger(Utilities::Misc::CONSOLE_LOG_AUDIO),
    _musicSource(), _soundSource() {
}

bool AudioService::initializeAudio() {
  _device.getActual();
  _context.getActual();
  alGenSources(1, &_musicSource);
  alGenSources(1, &_soundSource);
  alSourcef(_musicSource, AL_GAIN, 0.75f);
  alSourcef(_soundSource, AL_GAIN, 0.75f);
  alSourcef(_musicSource, AL_PITCH, _pitch);
  alSourcef(_soundSource, AL_PITCH, _pitch);

  return isInitialised;
}

ALuint AudioService::readFile(std::string input) {
  SF_INFO info;
  info.format = 0;
  SNDFILE* file = sf_open(input.c_str(), SFM_READ, &info);

  if (file == nullptr) {
    _logger.logErrorLine(std::string(sf_strerror(nullptr)));
  }

  std::vector<uint16_t> data;
  std::vector<short> readBuffer;
  readBuffer.resize(4096);

  size_t readSize = 0;

  while ((readSize = sf_read_short(file, readBuffer.data(), readBuffer.size())) != 0) {
    data.insert(data.end(), readBuffer.begin(), readBuffer.begin() + readSize);
  }

  ALuint buffer;
  alGenBuffers(1, &buffer);
  alBufferData(buffer, info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, &data.front(), data.size() * sizeof(uint16_t), info.samplerate);
  sf_close(file);
  return buffer;
}

void AudioService::load(std::string input, bool isMusic) {
  if (!isMusic) {
    auto exists = _sounds.find(input);
    if (exists != _sounds.end()) return;

    auto newSound = readFile(input);
    if (newSound != NULL) {
      _sounds[input] = newSound;
    } else {
      _logger.logError("OpenAL error occurred during load. Error: ", getALError());
    }
  } else {
    auto exists = _music.find(input);
    if (exists != _music.end()) return;

    auto newMusic = readFile(input);
    if (newMusic != NULL) {
      _music[input] = newMusic;
    } else {
      _logger.logError("OpenAL error occurred during load. Error: ", getALError());
    }
  }
}

void AudioService::unload(std::string input, bool isMusic) {
  if (!isMusic)
  {
    auto existingSound = _sounds.find(input);
    if (existingSound == _sounds.end()) return;

    alDeleteBuffers(1, &_sounds[input]);
    if (alGetError() != AL_NO_ERROR) {
      alSourcei(_soundSource, AL_BUFFER, 0);
      alDeleteBuffers(1, &_sounds[input]);
    }
    _sounds.erase(existingSound);
  }
  else
  {
    auto existingMusic = _music.find(input);
    if (existingMusic == _music.end()) return;

    alDeleteBuffers(1, &_music[input]);
    if (alGetError() != AL_NO_ERROR) {
      alSourcei(_musicSource, AL_BUFFER, 0);
      alDeleteBuffers(1, &_music[input]);
    }
    _music.erase(existingMusic);
  }
}

void AudioService::playSound(std::string soundName, int loops) {
  alSourcei(_soundSource, AL_BUFFER, _sounds[soundName]);
  alSourcef(_soundSource, AL_PITCH, _pitch);
  alSourcePlay(_soundSource);

  //Add loop logic
}

void AudioService::stopSound(std::string soundName) {
  alSourceStop(_soundSource);
}

void AudioService::setSoundVolume(std::string soundName, float value) {
  if (value > 1.0f) {
    alSourcef(_soundSource, AL_GAIN, 1.0f);
  } else if (value <= 0.0f) {
    alSourcef(_soundSource, AL_GAIN, 0.0f);
  } else {
    alSourcef(_soundSource, AL_GAIN, value);
  }
}

void AudioService::setSoundPosition(std::string soundName, int angle, int distance) {
  //TODO
}

void AudioService::setSoundDistance(std::string soundName, int distance) {
  //TODO
}

void AudioService::setSoundPanning(std::string soundName, int leftChannelVolume, int rightChannelVolume) {
  //TODO
}

void AudioService::resumeMusic() {
  alSourcePlay(_musicSource);
}

void AudioService::playMusic(std::string musicName, int loops) {
  auto buf = _music[musicName];
  alSourcei(_musicSource, AL_BUFFER, buf);
  //alSourcef(_musicSource, AL_PITCH, _pitch);
  alSourcePlay(_musicSource);

  //Add loop logic
}

void AudioService::pauseMusic() {
  alSourcePause(_musicSource);
}

void AudioService::stopMusic() {
  alSourceStop(_musicSource);
}

void AudioService::setMusicVolume(float value) {
  if (value > 1.0f) {
    alSourcef(_musicSource, AL_GAIN, 1.0f);
  }
  else if (value <= 0.0f) {
    alSourcef(_musicSource, AL_GAIN, 0.0f);
  }
  else {
    alSourcef(_musicSource, AL_GAIN, value);
  }
}

std::string AudioService::getALError() {
  auto err = alGetError();
  switch (err) {
    case AL_INVALID_NAME: {
      return std::string("A bad ID or name was passed to the OpenAL function.");
    }
    case AL_INVALID_ENUM: {
      return std::string("An invalid enum was passed to an OpenAL function.");
    }
    case AL_INVALID_VALUE: {
      return std::string("An invalid value was passed to an OpenAL function.");
    }
    case AL_INVALID_OPERATION: {
      return std::string("The requested operation is not valid.");
    }
    case AL_OUT_OF_MEMORY: {
      return std::string("The requested operation resulted in OpenAL running out of memory.");
    }
    default: {
      return std::string("");
    }
  }
}

AudioService::~AudioService() {
  if (!_music.empty()) {
    _music.clear();
  }
  if (!_sounds.empty()) {
    _sounds.clear();
  }

  if (!_context.isCreated()) return;

  alDeleteSources(1, &_soundSource);
  alDeleteSources(1, &_musicSource);

  _context.reset();
  _device.reset();
}

}
