// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsAdapter final : public GraphicsAdapter
    {
    private:
        VkPhysicalDevice _vulkanPhysicalDevice;
        NovelRT::Utilities::Lazy<VkPhysicalDeviceProperties> _vulkanPhysicalDeviceProperties;
        NovelRT::Utilities::Lazy<VkPhysicalDeviceMemoryProperties> _vulkanPhysicalDeviceMemoryProperties;
        NovelRT::Utilities::Lazy<std::string> _name;

        Threading::VolatileState _state;

        [[nodiscard]] std::string GetNameInternal();
        [[nodiscard]] VkPhysicalDeviceProperties GetVulkanPhysicalDevicePropertiesInternal();
        [[nodiscard]] VkPhysicalDeviceMemoryProperties GetVulkanPhysicalDeviceMemoryPropertiesInternal();

    public:
        VulkanGraphicsAdapter(const std::shared_ptr<VulkanGraphicsProvider>& provider, VkPhysicalDevice physicalDevice);

        [[nodiscard]] inline VkPhysicalDevice GetVulkanPhysicalDevice() const noexcept
        {
            return _vulkanPhysicalDevice;
        }

        [[nodiscard]] inline const VkPhysicalDeviceProperties& GetVulkanPhysicalDeviceProperties()
        {
            return _vulkanPhysicalDeviceProperties.getActual();
        }

        [[nodiscard]] inline const VkPhysicalDeviceMemoryProperties& GetVulkanPhysicalDeviceMemoryProperties()
        {
            return _vulkanPhysicalDeviceMemoryProperties.getActual();
        }

        [[nodiscard]] uint32_t GetDeviceId() final
        {
            return GetVulkanPhysicalDeviceProperties().deviceID;
        }

        [[nodiscard]] const std::string& GetName() final
        {
            return _name.getActual();
        }

        [[nodiscard]] inline uint32_t GetVendorId() final
        {
            return GetVulkanPhysicalDeviceProperties().vendorID;
        }

        [[nodiscard]] std::shared_ptr<GraphicsDevice> CreateDevice(
            std::shared_ptr<GraphicsSurfaceContext> surfaceContext,
            int32_t contextCount) final
        {
            return std::static_pointer_cast<GraphicsDevice>(CreateVulkanGraphicsDevice(
                std::dynamic_pointer_cast<VulkanGraphicsSurfaceContext>(surfaceContext), contextCount));
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsProvider> GetProvider() const
        {
            return std::dynamic_pointer_cast<VulkanGraphicsProvider>(GraphicsAdapter::GetProvider());
        }

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> CreateVulkanGraphicsDevice(
            std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
            int32_t contextCount);

        ~VulkanGraphicsAdapter() final = default;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSADAPTER_H
