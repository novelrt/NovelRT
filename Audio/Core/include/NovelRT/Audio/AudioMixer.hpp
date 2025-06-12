#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/AudioSourceContext.hpp>
#include <NovelRT/Audio/AudioSourceState.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace NovelRT::Audio
{
    template <typename TBackend>
    class AudioProvider;

    template <typename TBackend>
    class AudioMixer
    {
    private:
        std::shared_ptr<AudioProvider<TBackend>> _audioProvider;
        std::unordered_map<uint32_t, AudioSourceContext> _sourceContextCache;

    public:
        explicit AudioMixer(std::shared_ptr<AudioProvider<TBackend>> provider)
            : _audioProvider(std::move(provider)),
            _sourceContextCache()
        { }

        ~AudioMixer() = default;

        uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Span<float> buffer,
                                   int32_t channelCount,
                                   int32_t originalSampleRate)
        {
            AudioSourceContext context{};
            context.Channels = channelCount;
            context.SampleRate = originalSampleRate;

            uint32_t id = _audioProvider->SubmitAudioBuffer(buffer, context);
            _sourceContextCache.emplace(id, context);
        }

        void PlaySource(uint32_t id)
        {
            _audioProvider->PlaySource(id);
        }

        void StopSource(uint32_t id)
        {
            _audioProvider->StopSource(id);
        }

        void PauseSource(uint32_t id)
        {
            _audioProvider->PauseSource(id);
        }

        AudioSourceContext& GetSourceContext(uint32_t id)
        {
            return _sourceContextCache.at(id);
        }

        void SetSourceContext(uint32_t id, AudioSourceContext& context)
        {
            _sourceContextCache.at(id) = context;
        }

        void SetSourceVolume(uint32_t id, float volume)
        {
            _sourceContextCache[id].Volume = volume;
        }

        void SetSourcePitch(uint32_t id, float pitch)
        {
            _sourceContextCache[id].Pitch = pitch;
        }

        void SetSourceLoop(uint32_t id, bool isLooping)
        {
            _sourceContextCache[id].Loop = isLooping;
        }

        AudioSourceState GetSourceState(uint32_t id)
        {
            return _audioProvider.GetSourceState(id);
        }
    };
}
