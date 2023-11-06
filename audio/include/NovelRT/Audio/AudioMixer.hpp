// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <cstdint>
#include <memory>
#include <NovelRT/Audio/IAudioProvider.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Audio
{
    class AudioMixer
    {
        private:
            std::unique_ptr<IAudioProvider> _audioProvider;
            void TearDown();

        public:
            void Initialise();
            void SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer);
            void PlayOutputStream();
            void StopOutputStream();
            ~AudioMixer();
    };
}
