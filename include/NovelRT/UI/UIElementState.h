// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIELEMENTSTATE_H
#define NOVELRT_UI_UIELEMENTSTATE_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the UI namespace subset.
#endif

namespace NovelRT::UI
{
    enum class UIElementState : uint32_t
    {
        Disposed = 0,
        Hidden = 1, 
        Shown = 2,
        ToFadeIn = 3,
        FadingIn = 4,
        ToFadeOut = 5,
        FadingOut = 6,
    };
}

#endif // !NOVELRT_UI_UIELEMENTSTATE_H
