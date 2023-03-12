// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIELEMENTTYPE_H
#define NOVELRT_UI_UIELEMENTTYPE_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the UI namespace subset.
#endif

namespace NovelRT::UI
{
    enum class UIElementType : uint32_t
    {
        Generic = 0,
        Panel = 1,
        Button = 2,
        Textbox = 3,
        Text = 4
    };
}
#endif // NOVELRT_UI_UIELEMENTTYPE_H
