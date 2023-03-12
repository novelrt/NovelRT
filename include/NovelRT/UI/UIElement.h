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
        const char* Identifier;
        UIElementState State = NovelRT::UI::UIElementState::Hidden;
        UIElementType Type = NovelRT::UI::UIElementType::Generic;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F Scale;
        NovelRT::Graphics::RGBAColour Colour;
        NovelRT::Atom InternalIdentifier;

        inline UIElement& operator+=(const UIElement& other) noexcept
        {
            Identifier = other.Identifier;
            State = other.State;
            Type = other.Type;
            Position = other.Position;
            Scale = other.Scale;
            Colour = other.Colour;
            InternalIdentifier = other.InternalIdentifier;
            return *this;
        };

        friend inline bool operator==(const UIElement& lhs, const UIElement& rhs) noexcept
        {
            return lhs.InternalIdentifier == rhs.InternalIdentifier;
        }

        friend inline bool operator!=(const UIElement& lhs, const UIElement& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}

#endif // NOVELRT_UI_UIELEMENT_H
