#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/IGraphicsAdapterSelector.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;

    class VulkanGraphicsAdapterSelector
    {
    public:
        // NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this is intentionally non-static
        [[nodiscard]] std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider<VulkanGraphicsBackend>>& provider,
            const std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>>& surfaceContext,
            const std::vector<std::string>& requiredDeviceExtensions,
            const std::vector<std::string>& optionalDeviceExtensions) const;

        // NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this is intentionally non-static
        [[nodiscard]] std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider<VulkanGraphicsBackend>>& provider,
            const std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>>& surfaceContext) const;
    };
}
