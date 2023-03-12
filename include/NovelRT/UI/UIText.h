// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UITEXT_H
#define NOVELRT_UI_UITEXT_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIText
    {
    public:
        const char* Text;
        UIElementState State = NovelRT::UI::UIElementState::Hidden;
        UIElementType Type = NovelRT::UI::UIElementType::Generic;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Graphics::RGBAColour Colour;
        NovelRT::Atom Entity;

        inline UIText& operator+=(const UIText& other) noexcept
        {
            Text = other.Text;
            State = other.State;
            Type = other.Type;
            Position = other.Position;
            Colour = other.Colour;
            Entity = other.Entity;
            return *this;
        };

        friend inline bool operator==(const UIText& lhs, const UIText& rhs) noexcept
        {
            return lhs.Text == rhs.Text && lhs.State == rhs.State && lhs.Type == rhs.Type && lhs.Position == rhs.Position && lhs.Entity == rhs.Entity;
        }

        friend inline bool operator!=(const UIText& lhs, const UIText& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}

#endif // NOVELRT_UI_UITEXT_H
