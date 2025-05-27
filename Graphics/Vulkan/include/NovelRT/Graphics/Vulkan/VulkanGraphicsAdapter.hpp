#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <string>
#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsAdapter<Vulkan::VulkanGraphicsBackend> : public std::enable_shared_from_this<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> _provider;

        VkPhysicalDevice _physicalDevice;
        mutable NovelRT::Utilities::Lazy<VkPhysicalDeviceProperties> _physicalDeviceProperties;
        mutable NovelRT::Utilities::Lazy<VkPhysicalDeviceMemoryProperties> _physicalDeviceMemoryProperties;
        mutable NovelRT::Utilities::Lazy<std::string> _name;

    public:
        GraphicsAdapter(std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> provider, VkPhysicalDevice physicalDevice);
        ~GraphicsAdapter() noexcept = default;

        [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const noexcept;
        [[nodiscard]] const VkPhysicalDeviceProperties& GetPhysicalDeviceProperties() const;
        [[nodiscard]] const VkPhysicalDeviceMemoryProperties& GetPhysicalDeviceMemoryProperties() const;

        [[nodiscard]] uint32_t GetDeviceId() const;
        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> GetProvider() const;
        [[nodiscard]] uint32_t GetVendorId() const;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> CreateDevice(
            const std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>>& surfaceContext,
            int32_t contextCount);
    };
}
