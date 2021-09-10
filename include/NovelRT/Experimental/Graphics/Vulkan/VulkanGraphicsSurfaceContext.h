// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSSURFACECONTEXT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSSURFACECONTEXT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
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
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSSURFACECONTEXT_H
