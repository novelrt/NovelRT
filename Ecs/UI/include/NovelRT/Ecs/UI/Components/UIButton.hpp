#pragma once

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>

#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UIButton
    {
        const char* label = "";
        uint64_t eventId = std::numeric_limits<uint64_t>::max();
        NovelRT::Graphics::RGBAColour bgColour = NovelRT::Graphics::RGBAColour(0, 0, 0, 255);
        NovelRT::Graphics::RGBAColour activeColour = NovelRT::Graphics::RGBAColour(0, 0, 0, 255);
        NovelRT::Graphics::RGBAColour hoveredColour = NovelRT::Graphics::RGBAColour(0, 0, 0, 255);
        NovelRT::Graphics::RGBAColour textColour = NovelRT::Graphics::RGBAColour(255, 255, 255, 255);

        inline UIButton& operator+=(const UIButton& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const UIButton& other) const noexcept
        {
            return label == other.label && bgColour == other.bgColour && activeColour == other.activeColour &&
                   hoveredColour == other.hoveredColour && textColour == other.textColour;
        }
    };
}