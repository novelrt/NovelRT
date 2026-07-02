#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/IGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;

    class VulkanGraphicsAdapterSelector
    {
    private:
        Logging::LoggingService _logger = Logging::LoggingService("GFX");

        [[nodiscard]] int32_t RateDeviceSuitability(
            const GraphicsAdapter<Vulkan::VulkanGraphicsBackend>& adapter,
            const GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>& surfaceContext,
            const std::vector<FeatureProviderExtensionGroup>& requiredDeviceExtensions,
            const std::vector<FeatureProviderExtensionGroup>& optionalDeviceExtensions) const;

    public:
        // NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this is intentionally non-static
        [[nodiscard]] std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider<VulkanGraphicsBackend>>& provider,
            const std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>>& surfaceContext,
            const std::vector<FeatureProviderExtensionGroup>& requiredDeviceExtensions,
            const std::vector<FeatureProviderExtensionGroup>& optionalDeviceExtensions) const;

        // NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this is intentionally non-static
        [[nodiscard]] std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider<VulkanGraphicsBackend>>& provider,
            const std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>>& surfaceContext) const;
    };
}
