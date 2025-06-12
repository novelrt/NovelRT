#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/AudioSourceContext.hpp>
#include <NovelRT/Audio/AudioSourceState.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

namespace NovelRT::Audio
{
    template <typename TBackend>
    class AudioProvider : std::enable_shared_from_this<AudioProvider<TBackend>>
    {
    public:
        explicit AudioProvider() = delete;
        ~AudioProvider() = default;

        uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Span<float> buffer,
                                   AudioSourceContext& context);
        void PlaySource(uint32_t sourceId);
        void StopSource(uint32_t sourceId);
        void PauseSource(uint32_t sourceId);
        void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context);
        AudioSourceState GetSourceState(uint32_t id);
    };
}
