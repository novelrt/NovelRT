#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPluginProvider final : public PluginManagement::IGraphicsPluginProvider
    {
    protected:
        NovelRT::Utilities::Lazy<std::shared_ptr<VulkanGraphicsProvider>> _graphicsProvider;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsProvider> CreateVulkanGraphicsProviderInternal();

        [[nodiscard]] VulkanGraphicsProvider* GetGraphicsProviderInternal() override;

    public:
        VulkanGraphicsPluginProvider() noexcept;
        ~VulkanGraphicsPluginProvider() final = default;

        [[nodiscard]] std::shared_ptr<GraphicsAdapter> GetDefaultSelectedGraphicsAdapterForContext(
            std::shared_ptr<GraphicsSurfaceContext> context) override;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsAdapter> GetDefaultSelectedGraphicsAdapterForContextVulkan(
            std::shared_ptr<VulkanGraphicsSurfaceContext> context);

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsProvider> GetGraphicsProvider()
        {
            return std::dynamic_pointer_cast<VulkanGraphicsProvider>(GetGraphicsProviderInternal()->shared_from_this());
        }

        [[nodiscard]] std::shared_ptr<GraphicsSurfaceContext> CreateSurfaceContext(
            std::shared_ptr<IGraphicsSurface> surface) override;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsSurfaceContext> CreateSurfaceContextVulkan(
            std::shared_ptr<IGraphicsSurface> surface);
    };
}
