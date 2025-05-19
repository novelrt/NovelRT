#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsSurfaceContext
    {
    private:
        IGraphicsSurface* _surface;
        VulkanGraphicsProvider* _provider;
        LoggingService _logger;
        VkSurfaceKHR _vulkanSurface;

    public:
        VulkanGraphicsSurfaceContext(IGraphicsSurface* surface,
                                     VulkanGraphicsProvider* provider);

        ~VulkanGraphicsSurfaceContext();

        [[nodiscard]] inline void* GetSurfaceContextHandleUntyped()
        {
            return &_vulkanSurface;
        }

        [[nodiscard]] inline VkSurfaceKHR GetVulkanSurfaceContextHandle() const noexcept
        {
            return _vulkanSurface;
        }

        [[nodiscard]] inline IGraphicsSurface* GetSurface() const noexcept
        {
            return _surface;
        }

        [[nodiscard]] inline VulkanGraphicsProvider* GetProvider() const noexcept
        {
            return _provider;
        }

        template<typename THandleType>[[nodiscard]] THandleType GetSurfaceContextHandleAs()
        {
            return *reinterpret_cast<THandleType*>(GetSurfaceContextHandleUntyped());
        }
    };
}
