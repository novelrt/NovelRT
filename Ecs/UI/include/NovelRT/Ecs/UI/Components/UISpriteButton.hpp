#pragma once

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Ecs/UI/Components/UIButton.hpp>

#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UISpriteButton : UIButton
    {
        NovelRT::Graphics::RGBAColour tint = NovelRT::Graphics::RGBAColour(255,255,255,255);

        inline UISpriteButton& operator+=(const UISpriteButton& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const UISpriteButton& other) const noexcept
        {
            return tint == other.tint
                && label == other.label
                && bgColour == other.bgColour
                && activeColour == other.activeColour
                && hoveredColour == other.hoveredColour
                && textColour == other.textColour;
        }

        [[nodiscard]] inline bool operator!=(const UISpriteButton& other) const noexcept
        {
            return !(*this == other);
        }
    };
}