// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <cstdint>
#include <memory>
#include <map>
#include <NovelRT/Audio/IAudioProvider.hpp>
#include <NovelRT/Audio/AudioSourceContext.hpp>
#include <NovelRT/Audio/AudioSourceState.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Audio
{
    class AudioMixer
    {
        private:
            std::unique_ptr<IAudioProvider> _audioProvider;
            std::map<uint32_t, AudioSourceContext> _sourceContextCache;
            void TearDown();

        public:
            void Initialise();
            uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, int32_t channelCount, int32_t originalSampleRate);
            void PlaySource(uint32_t id);
            void StopSource(uint32_t id);
            void PauseSource(uint32_t id);
            AudioSourceContext& GetSourceContext(uint32_t id);
            void SetSourceContext(uint32_t id, AudioSourceContext& context);
            void SetSourceVolume(uint32_t id, float volume);
            void SetSourcePitch(uint32_t id, float pitch);
            void SetSourceLoop(uint32_t id, bool isLooping);
            AudioSourceState GetSourceState(uint32_t id);

            ~AudioMixer();
    };
}
