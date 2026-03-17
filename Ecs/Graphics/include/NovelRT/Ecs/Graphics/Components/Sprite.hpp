#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::Graphics::Components
{
    struct Sprite
    {
        inline Sprite& operator+=(const Sprite& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Sprite& /* other */) const noexcept
        {
            // TODO: implement this
            return true;
        }

        [[nodiscard]] inline bool operator!=(const Sprite& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
