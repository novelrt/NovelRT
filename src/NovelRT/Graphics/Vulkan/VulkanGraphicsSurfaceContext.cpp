// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{

    VulkanGraphicsSurfaceContext::VulkanGraphicsSurfaceContext(std::shared_ptr<IGraphicsSurface> surface,
                                                               const std::shared_ptr<VulkanGraphicsProvider>& provider)
        : GraphicsSurfaceContext(std::move(surface), std::static_pointer_cast<GraphicsProvider>(provider)),
          _logger(NovelRT::Core::LoggingService(NovelRT::Core::LoggingService::CONSOLE_LOG_GFX)),
          _vulkanSurface(VK_NULL_HANDLE)
    {
        std::shared_ptr<IGraphicsSurface> targetSurface = GetSurface();
        switch (targetSurface->GetKind())
        {
            case GraphicsSurfaceKind::Glfw:
            {
                auto func =
                    reinterpret_cast<VkResult (*)(VkInstance, void*, const VkAllocationCallbacks*, VkSurfaceKHR*)>(
                        targetSurface->GetContextHandle());

                VkResult funcResult =
                    func(GetProvider()->GetVulkanInstance(), targetSurface->GetHandle(), nullptr, &_vulkanSurface);
                if (funcResult != VK_SUCCESS)
                {
                    throw NovelRT::Core::Exceptions::InitialisationFailureException(
                        "Failed to initialise the VkSurfaceKHR.", funcResult);
                }

                _logger.logInfoLine("VkSurfaceKHR successfully created.");
                break;
            }
            case GraphicsSurfaceKind::Unknown:
            case GraphicsSurfaceKind::Android:
            case GraphicsSurfaceKind::Wayland:
            case GraphicsSurfaceKind::Win32:
            case GraphicsSurfaceKind::Xcb:
            case GraphicsSurfaceKind::Xlib:
            default:
                throw NovelRT::Core::Exceptions::NotSupportedException(
                    "The specified graphics surface kind is not supported by this graphics implementation.");
        }
    }

    VulkanGraphicsSurfaceContext::~VulkanGraphicsSurfaceContext()
    {
        vkDestroySurfaceKHR(GetProvider()->GetVulkanInstance(), _vulkanSurface, nullptr);
        _logger.logInfoLine("VkSurface successfully destroyed.");
    }
} // namespace NovelRT::Graphics::Vulkan
