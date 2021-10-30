// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT::Audio
{
    AudioService::AudioService()
        : _device(Utilities::Lazy<std::unique_ptr<ALCdevice, void (*)(ALCdevice*)>>(
              std::function<ALCdevice*()>([this] {
                  auto device = alcOpenDevice((_deviceName.empty()) ? nullptr : _deviceName.c_str());
                  if (!device)
                  {
                      std::string error = getALError();
                      _logger.logError("OpenAL device creation failed! {}", error);
                      throw Exceptions::InitialisationFailureException(
                          "OpenAL failed to create an audio device! Aborting...", error);
                  }
                  return device;
              }),
              [](auto x) { alcCloseDevice(x); })),
          _context(Utilities::Lazy<std::unique_ptr<ALCcontext, void (*)(ALCcontext*)>>(
              std::function<ALCcontext*()>([this] {
                  auto context = alcCreateContext(_device.getActual(), nullptr);
                  alcMakeContextCurrent(context);
                  isInitialised = true;
                  _deviceName = alcGetString(_device.getActual(), ALC_DEVICE_SPECIFIER);
                  _logger.logInfo("OpenAL Initialized on device: {}", _deviceName);
                  return context;
              }),
              [](auto x) {
                  alcMakeContextCurrent(nullptr);
                  alcDestroyContext(x);
              })),
          _logger(Utilities::Misc::CONSOLE_LOG_AUDIO),
          _manualLoad(false),
          _musicSource(),
          _musicSourceState(0),
          _musicLoopAmount(0),
          _soundLoopAmount(0),
          _soundSourceState(0),
          _soundStorage(),
          _bufferStorage(),
          isInitialised(false)
    {
    }

    bool AudioService::initializeAudio()
    {
        _device.getActual();
        _context.getActual();
        alGenSources(1, &_musicSource);
        alSourcef(_musicSource, AL_GAIN, 0.75f);
        alSourcef(_musicSource, AL_PITCH, _pitch);

        return isInitialised;
    }

    ALuint AudioService::readFile(std::string input)
    {
        SF_INFO info;
        info.format = 0;
        SNDFILE* file = sf_open(input.c_str(), SFM_READ, &info);

        if (file == nullptr)
        {
            _logger.logWarning(std::string(sf_strerror(nullptr)));
            return _noBuffer;
        }

        std::vector<uint16_t> data;
        std::vector<short> readBuffer;
        readBuffer.resize(_bufferSize);

        sf_count_t readSize = 0;

        while ((readSize = sf_read_short(file, readBuffer.data(), static_cast<sf_count_t>(readBuffer.size()))) != 0)
        {
            data.insert(data.end(), readBuffer.begin(), readBuffer.begin() + readSize);
        }

        ALuint buffer;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, &data.front(),
                     static_cast<ALsizei>(data.size() * sizeof(uint16_t)), info.samplerate);
        sf_close(file);
        return buffer;
    }

    /*Note: Due to the current design, this will currently block the thread it is being called on.
      If it is called on the main thread, please do all loading of audio files at the start of
      the engine (after NovelRunner has been created).
    */
    std::vector<ALuint>::iterator AudioService::loadMusic(std::string input)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot load new audio into memory while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::load", "You cannot load new audio when the service is not initialised.");
        }
        auto newBuffer = readFile(input);

        // Sorry Matt, nullptr types are incompatible to ALuint according to VS.
        if (newBuffer == _noBuffer)
        {
            _logger.logWarning("Could not load audio file: {}", input);
            return _music.end();
        }

        auto it = std::find(_music.begin(), _music.end(), newBuffer);
        if (it != _music.end())
        {
            alDeleteBuffers(1, &newBuffer);
            return it;
        }
        else
        {
            _music.push_back(newBuffer);
            _bufferStorage.push_back(newBuffer);
            it = std::find(_music.begin(), _music.end(), newBuffer);
            return it;
        }
    }

    void AudioService::setSoundVolume(ALuint source, float value)
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot change the volume of a nonexistent sound! the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::setSoundVolume",
                "You cannot modify a sound source when the AudioService is not initialised.");
        }

        if (value > 1.0f)
        {
            alSourcef(source, AL_GAIN, 1.0f);
        }
        else if (value <= 0.0f)
        {
            alSourcef(source, AL_GAIN, 0.0f);
        }
        else
        {
            alSourcef(source, AL_GAIN, value);
        }
    }

    // Switched to using two floats - for some reason VS complained when trying to use Maths::GeoVector2<float> here...
    // This also has no effect if the buffer is more than one channel (not Mono)
    void AudioService::setSoundPosition(ALuint source, float posX, float posY)
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot move audio position on a nonexistent sound! The service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::stopSound", "You cannot stop a sound when the AudioService is not initialised.");
        }

        alSource3f(source, AL_POSITION, posX, posY, 0.0f);
    }

    void AudioService::resumeMusic()
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot change the volume of a nonexistent sound! The service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::setSoundVolume",
                "You cannot modify a sound source when the AudioService is not initialised.");
        }

        alSourcePlay(_musicSource);
    }

    void AudioService::playMusic(std::vector<ALuint>::iterator handle, int32_t loops)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot play audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::playMusic", "You cannot play a sound when the AudioService is not initialised.");
        }

        if (handle == _music.end())
        {
            _logger.logWarning("Cannot play the requested sound - it may have been deleted or not loaded properly.");
            return;
        }

        alGetSourcei(_musicSource, AL_SOURCE_STATE, &_musicSourceState);
        if (_musicSourceState == AL_PLAYING)
        {
            alSourceStop(_musicSource);
            alGetSourcei(_musicSource, AL_SOURCE_STATE, &_musicSourceState);
        }
        alSourcei(_musicSource, AL_BUFFER, static_cast<ALint>(*handle));
        if (loops == -1 || loops > 0)
        {
            _musicLoopAmount = loops;
            alSourcei(_musicSource, AL_LOOPING, AL_TRUE);
        }
        else
        {
            alSourcei(_musicSource, AL_LOOPING, AL_FALSE);
        }
        alSourcePlay(_musicSource);
    }

    void AudioService::pauseMusic()
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot pause audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::pauseMusic", "You cannot pause a sound when the AudioService is not initialised.");
        }

        alSourcePause(_musicSource);
    }

    void AudioService::stopMusic()
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot stop audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::stopMusic", "You cannot stop a sound when the AudioService is not initialised.");
        }

        alSourceStop(_musicSource);
    }

    void AudioService::setMusicVolume(float value)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot modify audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::setMusicVolume", "You cannot modify a sound when the AudioService is not initialised.");
        }

        if (value > 1.0f)
        {
            alSourcef(_musicSource, AL_GAIN, 1.0f);
        }
        else if (value <= 0.0f)
        {
            alSourcef(_musicSource, AL_GAIN, 0.0f);
        }
        else
        {
            alSourcef(_musicSource, AL_GAIN, value);
        }
    }

    void AudioService::checkSources()
    {
        // Changing the init check as I don't want this to kill the Runner.
        if (isInitialised)
        {

            int32_t musicLoop = 0;
            int32_t soundLoop = 0;
            for (auto sound : _soundStorage)
            {
                alGetSourcei(sound, AL_LOOPING, &soundLoop);
                if (soundLoop == AL_TRUE)
                {
                    alGetSourcei(sound, AL_SOURCE_STATE, &_soundSourceState);
                    // Pretty sure there's a better way to check this...
                    if (_soundSourceState == AL_STOPPED && (_soundLoopAmount > 0 || _soundLoopAmount == -1))
                    {
                        if (_soundLoopAmount > 0)
                        {
                            _soundLoopAmount--;
                        }
                        alSourceRewind(sound);
                        alSourcePlay(sound);
                    }
                }
            }

            alGetSourcei(_musicSource, AL_LOOPING, &musicLoop);

            if (musicLoop == AL_TRUE)
            {
                alGetSourcei(_musicSource, AL_SOURCE_STATE, &_musicSourceState);
                if (_musicSourceState == AL_STOPPED && (_musicLoopAmount > 0 || _musicLoopAmount == -1))
                {
                    if (_musicLoopAmount > 0)
                    {
                        _musicLoopAmount--;
                    }
                    alSourceRewind(_musicSource);
                    alSourcePlay(_musicSource);
                }
            }
        }
    }

    std::string AudioService::getALError()
    {
        auto err = alGetError();
        switch (err)
        {
            case AL_INVALID_NAME:
            {
                return std::string("A bad ID or name was passed to the OpenAL function.");
            }
            case AL_INVALID_ENUM:
            {
                return std::string("An invalid enum was passed to an OpenAL function.");
            }
            case AL_INVALID_VALUE:
            {
                return std::string("An invalid value was passed to an OpenAL function.");
            }
            case AL_INVALID_OPERATION:
            {
                return std::string("The requested operation is not valid.");
            }
            case AL_OUT_OF_MEMORY:
            {
                return std::string("The requested operation resulted in OpenAL running out of memory.");
            }
            default:
            {
                return std::string("");
            }
        }
    }

    ALuint AudioService::loadSound(std::string input)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot load new audio into memory while the service is yolo uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::load", "You cannot load new audio when the service is not initialised.");
        }
        auto newBuffer = readFile(input);

        if (newBuffer == _noBuffer)
        {
            _logger.logWarning("Could not load audio file: {}", input);
            return _noBuffer;
        }

        _manualLoad = true;
        ALuint newSource = _noBuffer;
        alGenSources(1, &newSource);
        alSourcef(newSource, AL_GAIN, 0.75f);
        alSourcef(newSource, AL_PITCH, _pitch);
        alSourcei(newSource, AL_BUFFER, static_cast<ALint>(newBuffer));

        _soundStorage.push_back(newSource);
        _bufferStorage.push_back(newBuffer);

        return newSource;
    }

    void AudioService::unload(ALuint source)
    {
        alSourcei(source, AL_BUFFER, 0);
    }

    void AudioService::playSound(ALuint handle, int32_t loops)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot play audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::playMusic", "You cannot play a sound when the AudioService is not initialised.");
        }

        if (handle == _noBuffer)
        {
            _logger.logError("Cannot play the requested sound - it may have been deleted or not loaded properly.");
            return;
        }

        if (loops == -1 || loops > 0)
        {
            _soundLoopAmount = loops;
            alSourcei(handle, AL_LOOPING, AL_TRUE);
        }
        else
        {
            alSourcei(handle, AL_LOOPING, AL_FALSE);
        }
        alSourcePlay(handle);
    }

    void AudioService::stopSound(ALuint handle)
    {
        alSourceStop(handle);
    }

    bool AudioService::isLoaded(std::vector<ALuint>::iterator handle)
    {
        return (handle != _music.end());
    }

    bool AudioService::isLoaded(ALuint handle)
    {
        return (handle != _noBuffer);
    }

    void AudioService::tearDown()
    {
        if (!_context.isCreated())
            return;

        if (_manualLoad)
        {
            for (auto source : _soundStorage)
            {
                alDeleteSources(1, &source);
            }
            _soundStorage.clear();
        }

        alDeleteSources(1, &_musicSource);
        if (!_music.empty())
        {
            _music.clear();
        }

        for (auto buffer : _bufferStorage)
        {
            alDeleteBuffers(1, &buffer);
        }

        // were deleting the objects explicitly here to ensure they're always deleted in the right order, lest you
        // summon the kraken. - Ruby
        _context.reset();
        _device.reset();
    }

    AudioService::~AudioService()
    {
        tearDown();
    }

} // namespace NovelRT::Audio
