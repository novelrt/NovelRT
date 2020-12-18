// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_WINDOWMODE_H
#define NOVELRT_WINDOWMODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Windowing {
    enum class WindowMode : int32_t {
        Windowed,
        Borderless,
        Fullscreen
    };
}

#endif //NOVELRT_WINDOWMODE_H
