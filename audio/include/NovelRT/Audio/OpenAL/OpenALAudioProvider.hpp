// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <NovelRT/Audio/IAudioProvider.hpp>
#include <al/al.h>
#include <al/alext.h>

namespace NovelRT::Audio::OpenAL
{
    class OpenALAudioProvider : public IAudioProvider
    {
        private:
            ALuint _outputSource;
            ALCdevice* _device;
            ALCcontext* _context;

            std::string GetALError();

        protected:
            void Dispose() final;

        public:
            OpenALAudioProvider();

            void OpenOutputStream() final;
            void CloseOutputStream() final;
            void PlayOutputStream() final;
            void StopOutputStream() final;
            void SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer) final;
    };
}
