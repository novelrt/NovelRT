#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/LoggingService.h>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>

namespace NovelRT::Graphics::Vulkan
{

    class VulkanGraphicsSurfaceContext final : public GraphicsSurfaceContext
    {
    private:
        LoggingService _logger;
        VkSurfaceKHR _vulkanSurface;

    public:
        VulkanGraphicsSurfaceContext(std::shared_ptr<IGraphicsSurface> surface,
                                     const std::shared_ptr<VulkanGraphicsProvider>& provider);

        [[nodiscard]] inline void* GetSurfaceContextHandleUntyped() final
        {
            return &_vulkanSurface;
        }

        [[nodiscard]] inline VkSurfaceKHR GetVulkanSurfaceContextHandle() const noexcept
        {
            return _vulkanSurface;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsProvider> GetProvider() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsProvider>(GraphicsSurfaceContext::GetProvider());
        }

        ~VulkanGraphicsSurfaceContext() final;
    };
}
