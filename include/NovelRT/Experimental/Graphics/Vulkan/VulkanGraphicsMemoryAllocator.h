// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSMEMORYALLOCATOR_H
#define NOVELRT_VULKANGRAPHICSMEMORYALLOCATOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsMemoryAllocator final : public GraphicsMemoryAllocator
    {

    };
}

#endif // NOVELRT_VULKANGRAPHICSMEMORYALLOCATOR_H
