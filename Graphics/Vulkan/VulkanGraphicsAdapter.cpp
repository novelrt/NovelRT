// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>

#include <string>
#include <vector>

namespace NovelRT::Graphics
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

    VkPhysicalDeviceProperties ComputeDeviceProperties(VulkanGraphicsAdapter* adapter)
    {
        VkPhysicalDeviceProperties physicalDeviceProperties{};
        vkGetPhysicalDeviceProperties(adapter->GetPhysicalDevice(), &physicalDeviceProperties);
        return physicalDeviceProperties;
    }

    VkPhysicalDeviceMemoryProperties ComputeDeviceMemoryProperties(VulkanGraphicsAdapter* adapter)
    {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(adapter->GetPhysicalDevice(), &physicalDeviceMemoryProperties);
        return physicalDeviceMemoryProperties;
    }

    std::string ComputeName(VulkanGraphicsAdapter* adapter)
    {
        return { adapter->GetPhysicalDeviceProperties().deviceName };
    }

    VulkanGraphicsAdapter::GraphicsAdapter(
        std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> provider,
        VkPhysicalDevice physicalDevice)
        : _provider(std::move(provider))
        , _physicalDevice(physicalDevice)
        , _physicalDeviceProperties([this]() { return ComputeDeviceProperties(this); })
        , _physicalDeviceMemoryProperties([this]() { return ComputeDeviceMemoryProperties(this); })
        , _name([this]() { return ComputeName(this); })
    {
        if (!_provider)
        {
            throw Exceptions::NullPointerException(
                "The provided GraphicsProvider pointer is nullptr or an invalid pointer.");
        }
    }

    VkPhysicalDevice VulkanGraphicsAdapter::GetPhysicalDevice() const noexcept
    {
        return _physicalDevice;
    }

    const VkPhysicalDeviceProperties& VulkanGraphicsAdapter::GetPhysicalDeviceProperties() const
    {
        return _physicalDeviceProperties.Get();
    }

    const VkPhysicalDeviceMemoryProperties& VulkanGraphicsAdapter::GetPhysicalDeviceMemoryProperties() const
    {
        return _physicalDeviceMemoryProperties.Get();
    }

    uint32_t VulkanGraphicsAdapter::GetDeviceId() const
    {
        return _physicalDeviceProperties.Get().deviceID;
    }

    std::string VulkanGraphicsAdapter::GetName() const
    {
        return _name.Get();
    }

    std::shared_ptr<VulkanGraphicsProvider> VulkanGraphicsAdapter::GetProvider() const
    {
        return _provider;
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsAdapter::CreateDevice(
        const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext,
        int32_t contextCount)
    {
        return std::make_shared<VulkanGraphicsDevice>(
            this->shared_from_this(),
            surfaceContext, contextCount,
            std::vector<std::string>{ VK_KHR_SWAPCHAIN_EXTENSION_NAME },
            std::vector<std::string>{});
    }
}
