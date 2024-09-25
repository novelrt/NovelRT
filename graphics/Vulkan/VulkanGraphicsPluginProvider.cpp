// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/PluginManagement/IGraphicsPluginProvider.h>

// this is such a hack
using namespace NovelRT::PluginManagement;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

template<>
IGraphicsPluginProvider<VulkanGraphicsBackend>::IGraphicsPluginProvider() noexcept
    : _graphicsProvider([]() { return std::make_shared<VulkanGraphicsProvider>(); })
{
}

template<>
[[nodiscard]] std::shared_ptr<GraphicsProvider<VulkanGraphicsBackend>> IGraphicsPluginProvider<VulkanGraphicsBackend>::GetGraphicsProvider()
{
    return std::make_shared<GraphicsProvider<VulkanGraphicsBackend>>(_graphicsProvider.getActual());
}

template<>
std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>> IGraphicsPluginProvider<
    VulkanGraphicsBackend>::CreateSurfaceContext(std::shared_ptr<IGraphicsSurface> surface)
{
    return std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(surface, _graphicsProvider.getActual());
}

template<>
std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> IGraphicsPluginProvider<VulkanGraphicsBackend>::GetDefaultSelectedGraphicsAdapterForContext(std::shared_ptr<GraphicsSurfaceContext<VulkanGraphicsBackend>> context)
{
    auto x = VulkanGraphicsAdapterSelector()
        .GetDefaultRecommendedAdapter(
            _graphicsProvider.getActual(),
            context->_implementation);
    return std::make_shared<GraphicsAdapter<VulkanGraphicsBackend>>(x);
}