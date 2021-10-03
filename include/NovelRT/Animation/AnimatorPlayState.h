// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ANIMATION_ANIMATORPLAYSTATE_H
#define NOVELRT_ANIMATION_ANIMATORPLAYSTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation
{
    enum class AnimatorPlayState : uint32_t
    {
        Stopped,
        Playing,
        Paused
    };
}

#endif //! NOVELRT_ANIMATION_ANIMATORPLAYSTATE_H
