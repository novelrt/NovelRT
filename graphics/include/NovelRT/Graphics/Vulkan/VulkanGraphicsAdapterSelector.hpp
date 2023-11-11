#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/IGraphicsAdapterSelector.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapter;
    class VulkanGraphicsProvider;
    class VulkanGraphicsSurfaceContext;

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
