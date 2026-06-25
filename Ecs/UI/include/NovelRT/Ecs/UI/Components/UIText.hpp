#pragma once

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>

#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UIText
    {
        std::string* textValue;
        NovelRT::Graphics::RGBAColour colour = NovelRT::Graphics::RGBAColour(0, 0, 0, 255);

        inline UIText& operator+=(const UIText& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const UIText& other) const noexcept
        {
            if (textValue == nullptr || other.textValue == nullptr) {
                return false;
            }
            return *textValue == *other.textValue && colour.r == other.colour.r && colour.g == other.colour.g &&
                   colour.b == other.colour.b && colour.a == other.colour.a;
        }
    };
}
