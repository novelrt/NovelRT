#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Graphics::Components
{
    struct Camera
    {
        float left = -1.0f;
        float right = 1.0f;
        float bottom = -1.0f;
        float top = 1.0f;
        float nearPlane = 0.0f;
        float farPlane = 1.0f;
        bool isScreenSpace = false;

        inline Camera& operator+=(const Camera& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Camera& other) const noexcept
        {
            // normally I would care more about floating point comparison but this is basically only here to handle
            // deletion, where it'll always be zero. - Matt J.
            return left == other.left && right == other.right && bottom == other.bottom && top == other.top &&
                   nearPlane == other.nearPlane && farPlane == other.farPlane && isScreenSpace == other.isScreenSpace;
        }

        [[nodiscard]] inline bool operator!=(const Camera& other) const noexcept
        {
            return !(*this == other);
        }

        [[nodiscard]] static Camera GetDeleteInstructionState() noexcept
        {
            return Camera{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false};
        }
    };
}
