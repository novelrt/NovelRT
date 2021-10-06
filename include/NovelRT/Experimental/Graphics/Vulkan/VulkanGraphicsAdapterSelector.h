// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTERSELECTOR_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTERSELECTOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsAdapterSelector final : public IGraphicsAdapterSelector
    {
    private:
        [[nodiscard]] int32_t GetPhysicalDeviceOptionalExtensionSupportScore(
            VkPhysicalDevice physicalDevice) const noexcept;

        [[nodiscard]] int32_t RateDeviceSuitability(VkPhysicalDevice physicalDevice,
                                                    VkSurfaceKHR surfaceContext) const noexcept;

        [[nodiscard]] bool CheckPhysicalDeviceRequiredExtensionSupport(VkPhysicalDevice physicalDevice) const noexcept;

    public:
        [[nodiscard]] std::shared_ptr<GraphicsAdapter> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider>& provider,
            const std::shared_ptr<GraphicsSurfaceContext>& surfaceContext) const final;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsAdapter> GetDefaultRecommendedAdapterVulkan(
            const std::shared_ptr<VulkanGraphicsProvider>& provider,
            const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext) const;

        ~VulkanGraphicsAdapterSelector() final = default;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTERSELECTOR_H
