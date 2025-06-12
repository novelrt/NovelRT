#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/AudioProvider.hpp>
#include <NovelRT/Logging/LoggingService.hpp>

#include <vector>

#include <AL/al.h>
#include <AL/alext.h>

namespace NovelRT::Audio::OpenAL
{
    struct OpenALAudioBackend;
}

namespace NovelRT::Audio
{
    template<>
    class AudioProvider<OpenAL::OpenALAudioBackend>
        : std::enable_shared_from_this<AudioProvider<OpenAL::OpenALAudioBackend>>
    {
    private:
        LoggingService _logger;

        ALCdevice* _device;
        ALCcontext* _context;
        std::vector<uint32_t> _sources;
        std::vector<uint32_t> _buffers;

        uint32_t OpenSource(AudioSourceContext& context);

    public:
        explicit AudioProvider();
        ~AudioProvider();

        uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Span<float> buffer, AudioSourceContext& context);
        void PlaySource(uint32_t sourceId);
        void StopSource(uint32_t sourceId);
        void PauseSource(uint32_t sourceId);
        void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context);
        AudioSourceState GetSourceState(uint32_t id);
    };
}
