#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <optional>

namespace NovelRT::Graphics::Vulkan
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        [[nodiscard]] inline bool IsComplete() const noexcept
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
}
