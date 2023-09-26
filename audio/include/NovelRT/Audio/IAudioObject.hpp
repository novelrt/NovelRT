// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_IAUDIOOBJECT_HPP
#define NOVELRT_AUDIO_IAUDIOOBJECT_HPP

namespace NovelRT::Audio
{
    struct IAudioObject
    {
        int32_t id;
        NovelRT::Maths::GeoVector2F position;
        virtual ~IAudioObject();
    };
}

#endif // NOVELRT_AUDIO_IAUDIOOBJECT_HPP
