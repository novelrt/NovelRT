#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Logging/LoggingService.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        std::shared_ptr<IGraphicsSurface> _surface;
        std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> _provider;
        LoggingService _logger;
        VkSurfaceKHR _vulkanSurface;

    public:
        GraphicsSurfaceContext(std::shared_ptr<IGraphicsSurface> surface, std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> provider);
        ~GraphicsSurfaceContext();

        [[nodiscard]] VkSurfaceKHR GetSurfaceContextHandle() const noexcept;

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> GetProvider() const noexcept;
    };
}
