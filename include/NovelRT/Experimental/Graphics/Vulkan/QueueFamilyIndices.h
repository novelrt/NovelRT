// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_QUEUEFAMILYINDICES_H
#define NOVELRT_QUEUEFAMILYINDICES_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> commandQueueFamily;

        [[nodiscard]] inline bool IsComplete() const noexcept
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
}

#endif // NOVELRT_QUEUEFAMILYINDICES_H
