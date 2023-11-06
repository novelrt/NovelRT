// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
#include <NovelRT/Exceptions/Exceptions.h>

namespace NovelRT::Audio::OpenAL
{
    OpenALAudioProvider::OpenALAudioProvider()
    {
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

        OpenOutputStream();
    }

    void OpenALAudioProvider::Dispose()
    {
        CloseOutputStream();


    }

    void OpenALAudioProvider::OpenOutputStream()
    {
        alGenSources(1, &_outputSource);
        alSourcef(_outputSource, AL_GAIN, 0.75f);
        alSourcef(_outputSource, AL_PITCH, 1.0f);
    }

    void OpenALAudioProvider::CloseOutputStream()
    {
        alDeleteSources(1, &_outputSource);
    }

    void OpenALAudioProvider::PlayOutputStream()
    {

    }

    void OpenALAudioProvider::StopOutputStream()
    {

    }

    std::string OpenALAudioProvider::GetALError()
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

    void OpenALAudioProvider::SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer)
    {
        ALuint alBuffer;
        alGenBuffers(1, &alBuffer);
        alBufferData(alBuffer, AL_FORMAT_STEREO16, buffer.data(), static_cast<ALsizei>(buffer.size() * sizeof(int16_t)), 44100);
        alSourcei(_outputSource, AL_BUFFER, alBuffer);
    }
}
