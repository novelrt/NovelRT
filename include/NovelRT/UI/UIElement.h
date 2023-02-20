// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIELEMENT_H
#define NOVELRT_UI_UIELEMENT_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIElement
    {
    public:
        const char* Identifer;
        UIElementState State = NovelRT::UI::UIElementState::Hidden;
        UIElementType Type = NovelRT::UI::UIElementType::Generic;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F Scale;
        NovelRT::Graphics::RGBAColour Colour;
        NovelRT::Atom InternalIdentifier;
    };
}

#endif // NOVELRT_UI_UIELEMENT_H
