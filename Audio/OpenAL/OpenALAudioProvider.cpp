// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>

#include <AL/alext.h>

namespace NovelRT::Audio
{
    using OpenALAudioProvider = AudioProvider<OpenAL::OpenALAudioBackend>;

    static std::string GetALError(const LoggingService& logger)
    {
        auto err = alGetError();
        switch (err)
        {
            case AL_INVALID_NAME:
            {
                logger.logErrorLine("A bad ID or name was passed to the OpenAL function.");
                return std::string("A bad ID or name was passed to the OpenAL function.");
            }
            case AL_INVALID_ENUM:
            {
                logger.logErrorLine("An invalid enum was passed to an OpenAL function.");
                return std::string("An invalid enum was passed to an OpenAL function.");
            }
            case AL_INVALID_VALUE:
            {
                logger.logErrorLine("An invalid value was passed to an OpenAL function.");
                return std::string("An invalid value was passed to an OpenAL function.");
            }
            case AL_INVALID_OPERATION:
            {
                logger.logErrorLine("The requested operation is not valid.");
                return std::string("The requested operation is not valid.");
            }
            case AL_OUT_OF_MEMORY:
            {
                logger.logErrorLine("The requested operation resulted in OpenAL running out of memory.");
                return std::string("The requested operation resulted in OpenAL running out of memory.");
            }
            case AL_NO_ERROR:
            {
                return std::string();
            }
            default:
            {
                logger.logError("Unknown OpenAL Error - Code: {err}", err);
                return std::string("Unknown OpenAL Error - Code: " + std::to_string(err));
            }
        }
    }

    static void LogMessage(void* userptr, char level, const char* msg, int length) noexcept
    {
        const LoggingService& logger = *static_cast<LoggingService*>(userptr);
        std::string message(msg, length);

        switch(level)
        {
            case 'W':
            {
                logger.logWarningLine(message);
                break;
            }
            case 'E':
            {
                logger.logErrorLine(message);
                break;
            }
            case 'I':
            {
                logger.logInfoLine(message);
                break;
            }
            default:
            {
                logger.logDebugLine(message);
                break;
            }
        }
    }

    static void InstallLogger(const LoggingService& logger)
    {
        using callbackType = void ALC_APIENTRY(void* userptr, char level, const char* message, int length) noexcept;
        using fnType = void ALC_APIENTRY(callbackType* callback, void* userptr);

        void* callback = alcGetProcAddress(nullptr, "alsoft_set_log_callback");
        if (callback == nullptr)
        {
            return;
        }

        // We unfortunately cannot directly cast to void*, because of const-correctness.
        const void* tmp = static_cast<const void*>(&logger);
        reinterpret_cast<fnType*>(callback)(&LogMessage, const_cast<void*>(tmp));
    }

    static ALCdevice* CreateDevice(const LoggingService& logger)
    {
        InstallLogger(logger);

        auto* device = alcOpenDevice(nullptr);
        if (device == nullptr)
        {
            auto err = GetALError(logger);
            throw Exceptions::InitialisationFailureException("Failed to create OpenAL device:", err);
        }

        return device;
    }

    static ALCcontext* CreateContext(ALCdevice* device, const LoggingService& logger)
    {
        auto* context = alcCreateContext(device, nullptr);
        if (context == nullptr)
        {
            auto err = GetALError(logger);
            throw Exceptions::InitialisationFailureException("Failed to create OpenAL context:", err);
        }

        return context;
    }

    OpenALAudioProvider::AudioProvider()
        : _logger(NovelRT::Logging::CONSOLE_LOG_AUDIO),
          _device(CreateDevice(_logger)),
          _context(CreateContext(_device, _logger))
    {
        alcMakeContextCurrent(_context);
    }

    OpenALAudioProvider::~AudioProvider()
    {
        alGetError();
        alSourceStopv(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        GetALError(_logger);
        alDeleteSources(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        GetALError(_logger);
        _sources.clear();
        alDeleteBuffers(static_cast<int>(_buffers.size()), reinterpret_cast<ALuint*>(_buffers.data()));
        GetALError(_logger);
        _buffers.clear();
        alcMakeContextCurrent(NULL);
        alcDestroyContext(_context);
        alcCloseDevice(_device);
    }

    uint32_t OpenALAudioProvider::OpenSource(AudioSourceContext& context)
    {
        uint32_t source = 0;
        alGetError();
        alGenSources(1, &source);
        GetALError(_logger);
        alSourcef(source, AL_GAIN, context.Volume);
        GetALError(_logger);
        alSourcef(source, AL_PITCH, context.Pitch);
        GetALError(_logger);
        alSourcei(source, AL_LOOPING, static_cast<int>(context.Loop));
        GetALError(_logger);
        _sources.emplace_back(static_cast<uint32_t>(source));
        return source;
    }

    void OpenALAudioProvider::PlaySource(uint32_t sourceId)
    {
        alGetError();
        alSourcePlay(sourceId);
        GetALError(_logger);
    }

    void OpenALAudioProvider::StopSource(uint32_t sourceId)
    {
        alGetError();
        alSourceStop(sourceId);
        GetALError(_logger);
    }

    void OpenALAudioProvider::PauseSource(uint32_t sourceId)
    {
        alGetError();
        alSourcePause(sourceId);
        GetALError(_logger);
    }

    static ALenum DetermineChannelFormat(int32_t numberOfChannels)
    {
        switch(numberOfChannels)
        {
            case 1:
                return AL_FORMAT_MONO_FLOAT32;
            case 5:
                return AL_FORMAT_51CHN32;
            case 7:
                return AL_FORMAT_71CHN32;
            case 2:
            default:
                return AL_FORMAT_STEREO_FLOAT32;
        }
    }

    uint32_t OpenALAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Span<float> buffer, AudioSourceContext& context)
    {
        ALuint alBuffer;
        alGetError();
        alGenBuffers(1, &alBuffer);
        GetALError(_logger);
        alBufferData(alBuffer, DetermineChannelFormat(context.Channels), buffer.data(), static_cast<ALsizei>(buffer.size() * sizeof(float)), context.SampleRate);
        GetALError(_logger);
        _buffers.emplace_back(static_cast<uint32_t>(alBuffer));
        uint32_t sourceId = OpenSource(context);
        alSourcei(sourceId, AL_BUFFER, alBuffer);
        GetALError(_logger);
        return sourceId;
    }

    void OpenALAudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        alGetError();
        alSourcef(sourceId, AL_GAIN, context.Volume);
        GetALError(_logger);
        alSourcef(sourceId, AL_PITCH, context.Pitch);
        GetALError(_logger);
        alSourcei(sourceId, AL_LOOPING, static_cast<int>(context.Loop));
        GetALError(_logger);
    }

    static AudioSourceState ConvertToAudioSourceState(ALenum oALSourceState)
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
        GetALError(_logger);
        return ConvertToAudioSourceState(state);
    }
}
