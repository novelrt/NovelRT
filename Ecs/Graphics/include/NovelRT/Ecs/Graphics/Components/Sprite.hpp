#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/RGBAColour.hpp>
#include <uuid.h>

namespace NovelRT::Ecs::Graphics::Components
{
    struct Sprite
    {
        uuids::uuid assetId{};
        NovelRT::Graphics::RGBAColour tint = NovelRT::Graphics::RGBAColour(255, 255, 255, 255);

        inline Sprite& operator+=(const Sprite& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Sprite& other) const noexcept
        {
            return assetId == other.assetId && tint == other.tint;
        }

        [[nodiscard]] inline bool operator!=(const Sprite& other) const noexcept
        {
            return !(*this == other);
        }
    };
}