#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/IGraphicsAdapterSelector.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapterSelector
    {
    private:
        [[nodiscard]] static int32_t GetPhysicalDeviceOptionalExtensionSupportScore(
            VkPhysicalDevice physicalDevice) noexcept;

        [[nodiscard]] static int32_t RateDeviceSuitability(VkPhysicalDevice physicalDevice,
                                                    VkSurfaceKHR surfaceContext) noexcept;

        [[nodiscard]] static bool CheckPhysicalDeviceRequiredExtensionSupport(VkPhysicalDevice physicalDevice) noexcept;

    public:
        //NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this is intentionally non-static
        [[nodiscard]] std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> GetDefaultRecommendedAdapter(
            const GraphicsProvider<VulkanGraphicsBackend>* provider,
            const GraphicsSurfaceContext<VulkanGraphicsBackend>* surfaceContext) const;
    };
}
