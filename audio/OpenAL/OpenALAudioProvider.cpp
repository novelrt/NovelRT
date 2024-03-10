// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
#include <NovelRT/Exceptions/Exceptions.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace NovelRT::Audio::OpenAL
{
    typedef void (ALC_APIENTRY*LoggingCallback)(void*, char, const char*, int) noexcept;
    typedef void (ALC_APIENTRY*CallbackProvider)(LoggingCallback, void*) noexcept;

    OpenALAudioProvider::OpenALAudioProvider():
    _buffers(std::vector<uint32_t>()),
    _sources(std::vector<uint32_t>()),
    _logger(spdlog::stdout_color_mt("OpenAL"))
    {
        //Logger init
        _logger->set_level(spdlog::level::debug);
        CallbackProvider setLogCallback = reinterpret_cast<CallbackProvider>(alcGetProcAddress(nullptr, "alsoft_set_log_callback"));
        if (setLogCallback != nullptr)
        {
            setLogCallback(static_cast<LoggingCallback>([](void* ptr, char l, const char* m, int) noexcept
            {
                auto provider = reinterpret_cast<OpenALAudioProvider*>(ptr);
                provider->LogOpenALMessages(l, m);
            }), this);
        }


        //Device and Context Init
        _device = alcOpenDevice(nullptr);
        if(!_device)
        {
            std::string error = GetALError();
            throw Exceptions::InitialisationFailureException(
                "OpenAL failed to create an audio device!", error);
        }
        _context = alcCreateContext(_device, nullptr);
        if(!_context)
        {
            std::string error = GetALError();
            throw Exceptions::InitialisationFailureException(
                "OpenAL failed to create and attach a proper context!", error);
        }
        alcMakeContextCurrent(_context);
    }

    OpenALAudioProvider::~OpenALAudioProvider()
    {
        Dispose();
    }

    void OpenALAudioProvider::Dispose()
    {
        alGetError();
        alSourceStopv(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        GetALError();
        alDeleteSources(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        GetALError();
        _sources.clear();
        alDeleteBuffers(static_cast<int>(_buffers.size()), reinterpret_cast<ALuint*>(_buffers.data()));
        GetALError();
        _buffers.clear();
        alcMakeContextCurrent(NULL);
        GetALError();
        alcDestroyContext(_context);
        GetALError();
        alcCloseDevice(_device);
        GetALError();
    }

    uint32_t OpenALAudioProvider::OpenSource(AudioSourceContext& context)
    {
        uint32_t source = 0;
        alGetError();
        alGenSources(1, &source);
        GetALError();
        alSourcef(source, AL_GAIN, context.Volume);
        GetALError();
        alSourcef(source, AL_PITCH, context.Pitch);
        GetALError();
        alSourcei(source, AL_LOOPING, static_cast<int>(context.Loop));
        GetALError();
        _sources.emplace_back(static_cast<uint32_t>(source));
        return source;
    }

    // void OpenALAudioProvider::CloseSource()
    // {
    //     alDeleteSources(1, &_outputSource);
    // }

    void OpenALAudioProvider::PlaySource(uint32_t sourceId)
    {
        alGetError();
        alSourcePlay(sourceId);
        GetALError();
    }

    void OpenALAudioProvider::StopSource(uint32_t sourceId)
    {
        alGetError();
        alSourceStop(sourceId);
        GetALError();
    }

    void OpenALAudioProvider::PauseSource(uint32_t sourceId)
    {
        alGetError();
        alSourcePause(sourceId);
        GetALError();
    }

    std::string OpenALAudioProvider::GetALError()
    {
        auto err = alGetError();
        switch (err)
        {
            case AL_INVALID_NAME:
            {
                _logger->error("A bad ID or name was passed to the OpenAL function.");
                return std::string("A bad ID or name was passed to the OpenAL function.");
            }
            case AL_INVALID_ENUM:
            {
                _logger->error("An invalid enum was passed to an OpenAL function.");
                return std::string("An invalid enum was passed to an OpenAL function.");
            }
            case AL_INVALID_VALUE:
            {
                _logger->error("An invalid value was passed to an OpenAL function.");
                return std::string("An invalid value was passed to an OpenAL function.");
            }
            case AL_INVALID_OPERATION:
            {
                _logger->error("The requested operation is not valid.");
                return std::string("The requested operation is not valid.");
            }
            case AL_OUT_OF_MEMORY:
            {
                _logger->error("The requested operation resulted in OpenAL running out of memory.");
                return std::string("The requested operation resulted in OpenAL running out of memory.");
            }
            case AL_NO_ERROR:
            {
                return std::string();
            }
            default:
            {
                _logger->error("Unknown OpenAL Error - Code: {err}", err);
                return std::string("Unknown OpenAL Error - Code: " + err);
            }
        }
    }

    uint32_t OpenALAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context)
    {
        ALuint alBuffer;
        alGetError();
        alGenBuffers(1, &alBuffer);
        GetALError();
        alBufferData(alBuffer, DetermineChannelFormat(context.Channels), buffer.data(), static_cast<ALsizei>(buffer.size() * sizeof(int16_t)), context.SampleRate);
        GetALError();
        _buffers.emplace_back(static_cast<uint32_t>(alBuffer));
        uint32_t sourceId = OpenSource(context);
        alSourcei(sourceId, AL_BUFFER, alBuffer);
        GetALError();
        return sourceId;
    }

    void OpenALAudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        alGetError();
        alSourcef(sourceId, AL_GAIN, context.Volume);
        GetALError();
        alSourcef(sourceId, AL_PITCH, context.Pitch);
        GetALError();
        alSourcei(sourceId, AL_LOOPING, static_cast<int>(context.Loop));
        GetALError();
    }

    AudioSourceState OpenALAudioProvider::ConvertToAudioSourceState(ALenum oALSourceState)
    {
        switch(oALSourceState)
        {
            case AL_PLAYING:
            {
                return AudioSourceState::SOURCE_PLAYING;
            }
            case AL_PAUSED:
            {
                return AudioSourceState::SOURCE_PAUSED;
            }
            case AL_STOPPED:
            case AL_INITIAL:
            default:
            {
                return AudioSourceState::SOURCE_STOPPED;
            }
        }
    }

    AudioSourceState OpenALAudioProvider::GetSourceState(uint32_t sourceId)
    {
        ALenum state = 0x0;
        alGetError();
        alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
        GetALError();
        return ConvertToAudioSourceState(state);
    }

    ALenum OpenALAudioProvider::DetermineChannelFormat(int32_t numberOfChannels)
    {
        switch(numberOfChannels)
        {
            case 1:
                return AL_FORMAT_MONO16;
            case 5:
                return AL_FORMAT_51CHN16;
            case 7:
                return AL_FORMAT_71CHN16;
            case 2:
            default:
                return AL_FORMAT_STEREO16;
        }
    }

    void OpenALAudioProvider::LogOpenALMessages(char level, const char* message)
    {
        switch(level)
        {
            case 'W':
            {
                _logger->warn(message);
            }
            case 'E':
            {
                _logger->error(message);
            }
            case 'I':
            default:
            {
                _logger->debug(message);
            }
        }
    }
}
