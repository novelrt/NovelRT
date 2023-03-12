// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIPANEL_H
#define NOVELRT_UI_UIPANEL_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIPanel
    {
    public:
        const char* Identifier;
        UIElementState State = NovelRT::UI::UIElementState::Hidden;
        UIElementType Type = NovelRT::UI::UIElementType::Panel;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F Scale;
        NovelRT::Graphics::RGBAColour Colour;
        NovelRT::Atom InternalIdentifier;
        NovelRT::Atom RootElementId;

        inline UIPanel& operator+=(const UIPanel& other) noexcept
        {
            Identifier = other.Identifier;
            State = other.State;
            Type = other.Type;
            Position = other.Position;
            Scale = other.Scale;
            Colour = other.Colour;
            InternalIdentifier = other.InternalIdentifier;
            RootElementId = other.RootElementId;
            return *this;
        };

        friend inline bool operator==(const UIPanel& lhs, const UIPanel& rhs) noexcept
        {
            return lhs.Identifier == rhs.Identifier && lhs.State == rhs.State && lhs.Type == rhs.Type && lhs.Position == rhs.Position &&
                lhs.Scale == rhs.Scale && lhs.InternalIdentifier == rhs.InternalIdentifier && lhs.RootElementId == rhs.RootElementId;
        }

        friend inline bool operator!=(const UIPanel& lhs, const UIPanel& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    };
}

#endif // NOVELRT_UI_UIPANEL_H
