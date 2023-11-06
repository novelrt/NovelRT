// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#pragma once

#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Audio
{
    class IAudioProvider
    {
        protected:
            virtual void Dispose() = 0;

        public:
            virtual void OpenOutputStream() = 0;
            virtual void CloseOutputStream() = 0;
            virtual void SubmitAudioBuffer(const NovelRT::Utilities::Misc::Span<int16_t> buffer) = 0;
            virtual void PlayOutputStream() = 0;
            virtual void StopOutputStream() = 0;
            virtual ~IAudioProvider() = 0;

    };
}
