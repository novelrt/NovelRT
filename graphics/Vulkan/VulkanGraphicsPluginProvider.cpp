// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/Graphics.Vulkan.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsPluginProvider::VulkanGraphicsPluginProvider() noexcept
        : _graphicsProvider([&]() { return CreateVulkanGraphicsProviderInternal(); })
    {
    }

    std::shared_ptr<VulkanGraphicsProvider> VulkanGraphicsPluginProvider::CreateVulkanGraphicsProviderInternal()
    {
        return std::make_shared<VulkanGraphicsProvider>();
    }

    VulkanGraphicsProvider* VulkanGraphicsPluginProvider::GetGraphicsProviderInternal()
    {
        return _graphicsProvider.getActual().get();
    }

    std::shared_ptr<GraphicsSurfaceContext> VulkanGraphicsPluginProvider::CreateSurfaceContext(
        std::shared_ptr<IGraphicsSurface> surface)
    {
        return std::static_pointer_cast<GraphicsSurfaceContext>(CreateSurfaceContextVulkan(surface));
    }

    std::shared_ptr<VulkanGraphicsSurfaceContext> VulkanGraphicsPluginProvider::CreateSurfaceContextVulkan(
        std::shared_ptr<IGraphicsSurface> surface)
    {
        return std::make_shared<VulkanGraphicsSurfaceContext>(surface, GetGraphicsProvider());
    }

    std::shared_ptr<GraphicsAdapter> VulkanGraphicsPluginProvider::GetDefaultSelectedGraphicsAdapterForContext(
        std::shared_ptr<GraphicsSurfaceContext> context)
    {
        return std::static_pointer_cast<GraphicsAdapter>(GetDefaultSelectedGraphicsAdapterForContextVulkan(
            std::dynamic_pointer_cast<VulkanGraphicsSurfaceContext>(context)));
    }

    std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsPluginProvider::
        GetDefaultSelectedGraphicsAdapterForContextVulkan(std::shared_ptr<VulkanGraphicsSurfaceContext> context)
    {
        return VulkanGraphicsAdapterSelector().GetDefaultRecommendedAdapterVulkan(GetGraphicsProvider(), context);
    }
}
