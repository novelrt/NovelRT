#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Maths/GeoVector2F.hpp>

namespace NovelRT::Ecs::Graphics::Components
{
    /**
     * @brief A rectangle expressed as fractions of the rendering surface's dimensions.
     * x and y locate its top-left corner, measured from the surface's top-left corner.
     * X increases rightwards; Y increases downwards. {0, 0, 1, 1} fills the surface.
     * The renderer converts these values to pixels for the GPU viewport and scissor.
     */
    struct Viewport
    {
        float x = 0.0f;
        float y = 0.0f;
        float width = 1.0f;
        float height = 1.0f;

        inline Viewport& operator+=(const Viewport& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Viewport& other) const noexcept
        {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        [[nodiscard]] inline bool operator!=(const Viewport& other) const noexcept
        {
            return !(*this == other);
        }


        [[nodiscard]] static Maths::GeoVector2F ViewportDimensionsToVector2F(const Components::Viewport& viewport)
        {
            return Maths::GeoVector2F(viewport.width, viewport.height);
        }

        [[nodiscard]] static Maths::GeoVector2F ViewportLocationToVector2F(const Components::Viewport& viewport)
        {
            return Maths::GeoVector2F(viewport.x, viewport.y);
        }
    };
}
