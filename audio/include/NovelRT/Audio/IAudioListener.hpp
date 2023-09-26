// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_IAUDIOLISTENER_HPP
#define NOVELRT_AUDIO_IAUDIOLISTENER_HPP

namespace NovelRT::Audio
{
    struct IAudioListener : public IAudioObject
    {
        virtual ~IAudioListener();
    };
}

#endif // NOVELRT_AUDIO_IAUDIOLISTENER_HPP
