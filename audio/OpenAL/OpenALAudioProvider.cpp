// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
#include <NovelRT/Exceptions/Exceptions.h>

namespace NovelRT::Audio::OpenAL
{
    OpenALAudioProvider::OpenALAudioProvider()
    {
        _buffers = std::vector<uint32_t>();
        _sources = std::vector<uint32_t>();

        //Device and Context Init
        _device = alcOpenDevice(nullptr);
        if(!_device)
        {
            std::string error = GetALError();
            throw Exceptions::InitialisationFailureException(
                "OpenAL failed to create an audio device!", error);
        }
        _context = alcCreateContext(_device, nullptr);
        alcMakeContextCurrent(_context);
    }

    OpenALAudioProvider::~OpenALAudioProvider()
    {
        Dispose();
    }

    void OpenALAudioProvider::Dispose()
    {
        alSourceStopv(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        alDeleteSources(static_cast<int>(_sources.size()), reinterpret_cast<ALuint*>(_sources.data()));
        _sources.clear();
        alDeleteBuffers(static_cast<int>(_buffers.size()), reinterpret_cast<ALuint*>(_buffers.data()));
        _buffers.clear();
        alcMakeContextCurrent(NULL);
        alcDestroyContext(_context);
        alcCloseDevice(_device);
    }

    uint32_t OpenALAudioProvider::OpenSource(AudioSourceContext& context)
    {
        uint32_t source = 0;
        alGenSources(1, &source);
        alSourcef(source, AL_GAIN, context.Volume);
        alSourcef(source, AL_PITCH, context.Pitch);
        alSourcei(source, AL_LOOPING, static_cast<int>(context.Loop));
        _sources.emplace_back(static_cast<uint32_t>(source));
        return source;
    }

    // void OpenALAudioProvider::CloseSource()
    // {
    //     alDeleteSources(1, &_outputSource);
    // }

    void OpenALAudioProvider::PlaySource(uint32_t sourceId)
    {
        alSourcePlay(sourceId);
    }

    void OpenALAudioProvider::StopSource(uint32_t sourceId)
    {
        alSourceStop(sourceId);
    }

    void OpenALAudioProvider::PauseSource(uint32_t sourceId)
    {
        alSourcePause(sourceId);
    }

    void OpenALAudioProvider::GetALError()
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

    uint32_t OpenALAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context)
    {
        ALuint alBuffer;
        alGenBuffers(1, &alBuffer);
        alBufferData(alBuffer, DetermineChannelFormat(context.Channels), buffer.data(), static_cast<ALsizei>(buffer.size() * sizeof(int16_t)), context.SampleRate);
        _buffers.emplace_back(static_cast<uint32_t>(alBuffer));
        uint32_t sourceId = OpenSource(context);
        alSourcei(sourceId, AL_BUFFER, alBuffer);
        return sourceId;
    }

    void OpenALAudioProvider::SetSourceProperties(uint32_t sourceId, AudioSourceContext& context)
    {
        alSourcef(sourceId, AL_GAIN, context.Volume);
        alSourcef(sourceId, AL_PITCH, context.Pitch);
        alSourcei(sourceId, AL_LOOPING, static_cast<int>(context.Loop));
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
        alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
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

}
