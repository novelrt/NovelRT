// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_QUEUEFAMILYINDICES_H
#define NOVELRT_GRAPHICS_VULKAN_QUEUEFAMILYINDICES_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

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

#endif // NOVELRT_GRAPHICS_VULKAN_QUEUEFAMILYINDICES_H
