// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_WINDOWMODE_H
#define NOVELRT_WINDOWMODE_H

namespace NovelRT::Windowing
{
    enum class WindowMode : uint32_t
    {
        Windowed,
        Borderless,
        Fullscreen
    };
}

#endif // NOVELRT_WINDOWMODE_H
