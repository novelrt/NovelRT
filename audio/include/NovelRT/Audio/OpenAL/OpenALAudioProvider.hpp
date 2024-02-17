// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <NovelRT/Audio/IAudioProvider.hpp>
#include <al/al.h>
#include <al/alext.h>
#include <vector>

namespace NovelRT::Audio::OpenAL
{
    class OpenALAudioProvider : public IAudioProvider
    {
        private:
            ALuint _outputSource;
            ALCdevice* _device;
            ALCcontext* _context;
            std::vector<uint32_t> _sources;
            std::vector<uint32_t> _buffers;

            std::string GetALError();
            AudioSourceState ConvertToAudioSourceState(ALenum oalSourceState);

        protected:
            void Dispose() final;
            uint32_t OpenSource(AudioSourceContext& context) final;

        public:
            OpenALAudioProvider();
            void PlaySource(uint32_t sourceId) final;
            void StopSource(uint32_t sourceId) final;
            void PauseSource(uint32_t sourceId) final;
            void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context) final;
            uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t>& buffer, AudioSourceContext& context) final;
            AudioSourceState GetSourceState(uint32_t id) final;

            ~OpenALAudioProvider() final;
    };
}
