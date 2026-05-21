#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Graphics::Components
{
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
            return x == other.x &&
                   y == other.y &&
                   width == other.width &&
                   height == other.height;
        }

        [[nodiscard]] inline bool operator!=(const Viewport& other) const noexcept
        {
            return !(*this == other);
        }

        [[nodiscard]] static Viewport GetDeleteInstructionState() noexcept
        {
            return Viewport{0.0f, 0.0f, 0.0f, 0.0f};
        }
    };
}