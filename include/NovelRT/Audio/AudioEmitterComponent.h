// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_AUDIO_AUDIOEMITTERCOMPONENT_H
#define NOVELRT_AUDIO_AUDIOEMITTERCOMPONENT_H

namespace NovelRT::Audio
{
    struct AudioEmitterComponent
    {
        uint32_t handle;
        bool isMusic;
        int32_t numberOfLoops;
        Maths::GeoVector2F position;
        float volume;
    };
}

#endif // NOVELRT_AUDIO_AUDIOEMITTERCOMPONENT_H
