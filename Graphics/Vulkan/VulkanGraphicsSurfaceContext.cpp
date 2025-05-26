// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/NotSupportedException.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;

    VulkanGraphicsSurfaceContext::GraphicsSurfaceContext(
        std::weak_ptr<IGraphicsSurface> surface,
        std::shared_ptr<VulkanGraphicsProvider> provider)
        : _surface(std::move(surface))
        ,  _provider(std::move(provider))
        ,  _logger(LoggingService(NovelRT::Logging::CONSOLE_LOG_GFX))
        ,  _vulkanSurface(VK_NULL_HANDLE)
    {
        if (_surface.expired())
        {
            throw Exceptions::NullPointerException("The supplied IGraphicsSurface is nullptr.");
        }

        if (_provider == nullptr)
        {
            throw Exceptions::NullPointerException("The supplied GraphicsProvider is nullptr.");
        }

        auto surfacePtr = _surface.lock();
        switch (surfacePtr->GetKind())
        {
            case GraphicsSurfaceKind::Glfw:
            {
                auto func =
                    reinterpret_cast<VkResult (*)(VkInstance, void*, const VkAllocationCallbacks*, VkSurfaceKHR*)>(
                        surfacePtr->GetContextHandle());

                VkResult funcResult =
                    func(_provider->GetVulkanInstance(), surfacePtr->GetHandle(), nullptr, &_vulkanSurface);
                if (funcResult != VK_SUCCESS)
                {
                    throw Exceptions::InitialisationFailureException("Failed to initialise the VkSurfaceKHR.",
                                                                     funcResult);
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
                throw Exceptions::NotSupportedException(
                    "The specified graphics surface kind is not supported by this graphics implementation.");
        }
    }

    VulkanGraphicsSurfaceContext::~GraphicsSurfaceContext()
    {
        vkDestroySurfaceKHR(_provider->GetVulkanInstance(), _vulkanSurface, nullptr);
        _logger.logInfoLine("VkSurface successfully destroyed.");
    }

    VkSurfaceKHR VulkanGraphicsSurfaceContext::GetSurfaceContextHandle() const noexcept
    {
        return _vulkanSurface;
    }

    std::weak_ptr<IGraphicsSurface> VulkanGraphicsSurfaceContext::GetSurface() const noexcept
    {
        return _surface;
    }

    std::weak_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsSurfaceContext::GetProvider() const noexcept
    {
        return _provider;
    }
}
