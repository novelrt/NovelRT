// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <NovelRT/Utilities/Misc.h>
#include <NovelRT/Audio/AudioSourceContext.hpp>
#include <NovelRT/Audio/AudioSourceState.hpp>

namespace NovelRT::Audio
{
    class IAudioProvider
    {
        protected:
            virtual void Dispose() = 0;
            virtual uint32_t OpenSource(AudioSourceContext& context) = 0;

        public:
            virtual uint32_t SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer, AudioSourceContext& context) = 0;
            virtual void PlaySource(uint32_t sourceId) = 0;
            virtual void StopSource(uint32_t sourceId) = 0;
            virtual void PauseSource(uint32_t sourceId) = 0;
            virtual void SetSourceProperties(uint32_t sourceId, AudioSourceContext& context) = 0;
            virtual AudioSourceState GetSourceState(uint32_t id) = 0;

            virtual ~IAudioProvider() = default;

    };
}
