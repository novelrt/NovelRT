// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsAdapter final : public GraphicsAdapter
    {
    public:
        VulkanGraphicsAdapter(std::weak_ptr<GraphicsProvider> provider, VkPhysicalDevice physicalDevice);
        uint32_t GetDeviceId() const noexcept final;
        const std::string& GetName() const noexcept final;
        ~VulkanGraphicsAdapter() final = default;
    };
}

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H
