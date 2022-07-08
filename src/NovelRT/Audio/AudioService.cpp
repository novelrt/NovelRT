// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/Audio.h>

namespace NovelRT::Audio
{
    AudioService::AudioService()
        : _device(Utilities::Lazy<std::unique_ptr<ALCdevice, void (*)(ALCdevice*)>>(
              std::function<ALCdevice*()>([this] {
                  auto device = alcOpenDevice((_deviceName.empty()) ? nullptr : _deviceName.c_str());
                  if (!device)
                  {
                      std::string error = GetALError();
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
          _musicStopRequested(false),
          _musicLoopAmount(0),
          _soundLoopAmount(0),
          _soundSourceState(0),
          _soundStorage(),
          _bufferStorage(),
          isInitialised(false)
    {
    }

    bool AudioService::InitializeAudio()
    {
        _device.getActual();
        _context.getActual();
        alGenSources(1, &_musicSource);
        alSourcef(_musicSource, AL_GAIN, 0.75f);
        alSourcef(_musicSource, AL_PITCH, _pitch);

        return isInitialised;
    }

    ALuint AudioService::ReadFile(std::string input)
    {
        std::filesystem::path inputPath = std::filesystem::path(input);
        AudioFileInfo info = AudioFileInfo{};

        if(inputPath.extension() == ".ogg")
        {
            LoadVorbisFile(input, info);
        }
        else if(inputPath.extension() == ".wav")
        {
            LoadWaveFile(input, info);
        }
        else
        {
            _logger.logError("File specified at {} is not in a supported format!", input);
            return _noBuffer;
        }


        ALuint buffer;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, info.data, static_cast<ALsizei>(info.size), static_cast<ALsizei>(info.frequency));
        _logger.logDebugLine(GetALError());

        _logger.logDebug("Loaded {}\nChannels: {}, Sample Rate: {},\nSamples: {}, Buffer ID: {}", input, info.channels, info.frequency, info.size, buffer);

        delete(info.data);
        return buffer;
    }

    /*Note: Due to the current design, this will currently block the thread it is being called on.
      If it is called on the main thread, please do all loading of audio files at the start of
      the engine (after NovelRunner has been created).
    */
    std::vector<ALuint>::iterator AudioService::LoadMusic(std::string input)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot load new audio into memory while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::load", "You cannot load new audio when the service is not initialised.");
        }
        auto newBuffer = ReadFile(input);

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

    void AudioService::SetSoundVolume(ALuint source, float value)
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot change the volume of a nonexistent sound! the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::SetSoundVolume",
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
    void AudioService::SetSoundPosition(ALuint source, float posX, float posY)
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot move audio position on a nonexistent sound! The service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::StopSound", "You cannot stop a sound when the AudioService is not initialised.");
        }

        alSource3f(source, AL_POSITION, posX, posY, 0.0f);
    }

    void AudioService::ResumeMusic()
    {
        if (!isInitialised)
        {
            _logger.logError(
                "Cannot change the volume of a nonexistent sound! The service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::SetSoundVolume",
                "You cannot modify a sound source when the AudioService is not initialised.");
        }

        alSourcePlay(_musicSource);
        _musicStopRequested = false;
    }

    void AudioService::PlayMusic(std::vector<ALuint>::iterator handle, int32_t loops)
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
        _musicStopRequested = false;
    }

    void AudioService::PauseMusic()
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot pause audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::PauseMusic", "You cannot pause a sound when the AudioService is not initialised.");
        }

        _musicStopRequested = true;
        alSourcePause(_musicSource);
    }

    void AudioService::StopMusic()
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot stop audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::StopMusic", "You cannot stop a sound when the AudioService is not initialised.");
        }

        _musicStopRequested = true;
        alSourceStop(_musicSource);
    }

    void AudioService::SetMusicVolume(float value)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot modify audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::SetMusicVolume", "You cannot modify a sound when the AudioService is not initialised.");
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

    void AudioService::CheckSources()
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
                    if (_soundLoopAmount > 0)
                    {
                        _soundLoopAmount--;
                        if (_soundLoopAmount == 0)
                        {
                            alSourcei(sound, AL_LOOPING, AL_FALSE);
                        }
                    }
                }
            }

            alGetSourcei(_musicSource, AL_LOOPING, &musicLoop);

            if (musicLoop == AL_TRUE)
            {
                alGetSourcei(_musicSource, AL_SOURCE_STATE, &_musicSourceState);
                if (_musicLoopAmount > 0 && !_musicStopRequested)
                {
                    _musicLoopAmount--;
                    if (_musicLoopAmount == 0)
                    {
                        alSourcei(_musicSource, AL_LOOPING, AL_FALSE);
                    }
                }
            }
        }
    }

    std::string AudioService::GetALError()
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

    ALuint AudioService::LoadSound(std::string input)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot load new audio into memory while the service is yolo uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::load", "You cannot load new audio when the service is not initialised.");
        }
        auto newBuffer = ReadFile(input);

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

    void AudioService::Unload(ALuint source)
    {
        alSourcei(source, AL_BUFFER, 0);
    }

    void AudioService::PlaySound(ALuint handle, int32_t loops)
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

    void AudioService::StopSound(ALuint handle)
    {
        alSourceStop(handle);
    }

    bool AudioService::IsLoaded(std::vector<ALuint>::iterator handle)
    {
        return (handle != _music.end());
    }

    bool AudioService::IsLoaded(ALuint handle)
    {
        return (handle != _noBuffer);
    }

    void AudioService::TearDown()
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
        TearDown();
    }

    bool AudioService::IsMusicPlaying()
    {
        alGetSourcei(_musicSource, AL_SOURCE_STATE, &_musicSourceState);
        return (_musicSourceState == AL_PLAYING || _musicSourceState == AL_PAUSED);
    }

    bool AudioService::IsSoundPlaying(ALuint handle)
    {
        alGetSourcei(handle, AL_SOURCE_STATE, &_soundSourceState);
        return (_soundSourceState == AL_PLAYING || _soundSourceState == AL_PAUSED);
    }

    float AudioService::GetMusicVolume()
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot modify audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::SetMusicVolume", "You cannot modify a sound when the AudioService is not initialised.");
        }

        float result = 0.0f;
        alGetSourcef(_musicSource, AL_GAIN, &result);
        return result;
    }

    float AudioService::GetSoundVolume(ALuint handle)
    {
        if (!isInitialised)
        {
            _logger.logError("Cannot modify audio while the service is uninitialised! Aborting...");
            throw NovelRT::Exceptions::NotInitialisedException(
                "AudioService::SetMusicVolume", "You cannot modify a sound when the AudioService is not initialised.");
        }

        float result = 0.0f;
        alGetSourcef(handle, AL_GAIN, &result);
        return result;
    }

    //These are required to _not_ be defined as a member-bound function for ov_callbacks

    size_t StreamRead(void* buffer, size_t elementSize, size_t elementCount, void* dataSource)
    {
        assert(elementSize == 1);

        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        stream.read(static_cast<char*>(buffer), elementCount);
        const std::streamsize bytesRead = stream.gcount();
        stream.clear();
        return static_cast<size_t>(bytesRead);
    }

    int StreamSeek(void* dataSource, ogg_int64_t offset, int origin)
    {
        static const std::vector<std::ios_base::seekdir> seekDirections{std::ios_base::beg, std::ios_base::cur, std::ios_base::end};
        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        stream.seekg(offset, seekDirections.at(origin));
        stream.clear();
        return 0;
    }

    long StreamTell(void* dataSource)
    {
        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        const auto position = stream.tellg();
        assert(position >= 0);
        return static_cast<long>(position);
    }

    void AudioService::LoadVorbisFile(std::string input, AudioFileInfo& output)
    {
        OggVorbis_File file;
	    vorbis_info* info = nullptr;
        std::ifstream stream(input, std::ios::binary);

        if (!stream.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(input);
        }

        const ov_callbacks callbacks{StreamRead, StreamSeek, nullptr, StreamTell};

        // Open the Vorbis file via ov_open_callbacks with OV_CALLBACKS_NOCLOSE to ensure the file doesn't disappear
        // on Windows devices
        if(ov_open_callbacks(&stream, &file, nullptr, 0, callbacks) < 0)
        {
            throw NovelRT::Exceptions::IOException(input, "File provided does not contain a valid Ogg Vorbis stream.");
        }

        // Get the info struct from Ogg Vorbis
        info = ov_info(&file, -1);
        output.channels = info->channels;
        output.frequency = info->rate;

        // Get the size of data to read
        size_t length = ov_pcm_total(&file, -1) * info->channels * 2;
        output.size = static_cast<size_t>(length);

        //Allocate a buffer for the samples data
        output.data = malloc(length);
        if(output.data == 0)
        {
            throw NovelRT::Exceptions::NullPointerException("Unable to allocate memory when reading the sound file.");
        }

        // Read the samples at a sample size of 4096
        for(size_t sz = 0, offset = 0, sel = 0; (sz = ov_read(&file, (char*)output.data + offset, 4096, 0, sizeof(int16_t), 1, (int*)&sel)) != 0; offset += sz)
        {
            if(sz < 0)
            {
                if(sz == OV_HOLE)
                {
                    throw NovelRT::Exceptions::IOException(input, "Vorbis: Interruption in data while retrieving next packet.");
                }
                else if(sz == OV_EBADLINK)
                {
                    throw NovelRT::Exceptions::IOException(input, "Vorbis: Invalid stream section, or the requested link is corrupt.");
                }
                else //If its not the top two, it's OV_EINVAL
                {
                    throw NovelRT::Exceptions::IOException(input, "Vorbis: file headers are corrupt or could not be read.");
                }
            }
        }

        ov_clear(&file);
        stream.close();
    }

    void AudioService::LoadWaveFile(std::string input, AudioFileInfo& output)
    {
        std::ifstream stream(input, std::ios::binary);

        if (!stream.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(input);
        }

        stream.seekg(0, std::ios::beg);

        std::string headerId(4, ' ');
        std::string format(4, ' ');
        stream.read(&headerId[0], 4);

        stream.seekg(4,std::ios_base::cur);
        stream.read(&format[0], 4);

        if(headerId != "RIFF" || format != "WAVE")
        {
            throw NovelRT::Exceptions::NotSupportedException("The file format provided is not supported.");
        }

        std::string fmtHeader(4, ' ');
        stream.read(&fmtHeader[0], 4);

        if(fmtHeader != "fmt ")
        {
            throw NovelRT::Exceptions::NotSupportedException("The provided WAV file has an invalid or unsupported fmt subchunk.");
        }

        stream.seekg(4, std::ios_base::cur);

        int32_t fmtFormat = 0;
        stream.read(reinterpret_cast<char*>(&fmtFormat), 2);

        if(fmtFormat != 1)
        {
            throw NovelRT::Exceptions::NotSupportedException("The provided WAV file is in an unsupported format - NovelRT only supports PCM formatted WAV files at this time.");
        }

        int32_t channels = 0;
        stream.read(reinterpret_cast<char*>(&channels), 2);
        int32_t sampleRate = 0;
        stream.read(reinterpret_cast<char*>(&sampleRate), 4);

        stream.seekg(6, std::ios_base::cur);
        int32_t bitsPerSample = 0;
        stream.read(reinterpret_cast<char*>(&bitsPerSample), 2);

        if(bitsPerSample != 16)
        {
            throw NovelRT::Exceptions::NotSupportedException("The provided WAV file is in an unsupported format - NovelRT only supports 16-bit samples for WAV files at this time.");
        }

        std::string dataHeader(4, ' ');
        stream.read(&dataHeader[0], 4);

        if(dataHeader != "data")
        {
            throw NovelRT::Exceptions::NotSupportedException("The provided WAV file has an invalid or unsupported data subchunk.");
        }

        size_t size = 0;
        stream.read(reinterpret_cast<char*>(&size), 4);

        output.data = malloc(size);
        stream.read(reinterpret_cast<char*>(output.data), size);

        output.channels = channels;
        output.frequency = sampleRate;
        output.size = size;

        stream.close();
    }

} // namespace NovelRT::Audio
