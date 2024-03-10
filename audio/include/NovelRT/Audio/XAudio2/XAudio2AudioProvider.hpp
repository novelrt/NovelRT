// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <vector>
#include <map>
#include <NovelRT/Audio/IAudioProvider.hpp>
#include <spdlog/spdlog.h>
#include <xaudio2.h>

namespace NovelRT::Audio::XAudio2
{
    class XAudio2AudioProvider : public IAudioProvider
    {
        private:
            IXAudio2* _device;
            IXAudio2MasteringVoice* _masterVoice;
            std::map<uint32_t, IXAudio2SourceVoice*> _sources;
            uint32_t _sourceCounter;
            std::shared_ptr<spdlog::logger> _logger;
            uint32_t _bufferCounter;
            std::map<uint32_t, XAUDIO2_BUFFER> _buffers;
            HRESULT _hr;

            AudioSourceState ConvertToAudioSourceState(XAUDIO2_VOICE_STATE sourceState);

        protected:
            void Dispose() final;
            uint32_t OpenSource(AudioSourceContext& context) final;

        public:
            XAudio2AudioProvider();
            void PlaySource(uint32_t sourceId) final;
            void StopSource(uint32_t sourceId) final;
            void PauseSource(uint32_t sourceId) final;
            void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context) final;
            uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context) final;
            AudioSourceState GetSourceState(uint32_t id) final;

            ~XAudio2AudioProvider() final;
    };
}
