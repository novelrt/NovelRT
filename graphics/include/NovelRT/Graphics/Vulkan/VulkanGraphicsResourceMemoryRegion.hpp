#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <vma/vk_mem_alloc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsResource;

    class VulkanGraphicsResourceMemoryRegionBase
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
        std::shared_ptr<VulkanGraphicsResource> _owningResource;
        VmaVirtualAllocation _virtualAllocation;
        VmaVirtualAllocationInfo _virtualAllocationInfo;

    public:
        VulkanGraphicsResourceMemoryRegionBase(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                           std::shared_ptr<VulkanGraphicsResource> owningResource,
                                           VmaVirtualAllocation virtualAllocation,
                                           VmaVirtualAllocationInfo virtualAllocationInfo);

        ~VulkanGraphicsResourceMemoryRegionBase() = default;
        
        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsResource> GetOwningResource() const noexcept;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;
        
        [[nodiscard]] size_t GetRelativeOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] VmaVirtualAllocation GetVirtualAllocation() const noexcept;

        [[nodiscard]] VmaVirtualAllocationInfo GetVirtualAllocationInfo() const noexcept;
    };

    template<typename TResource>
    class VulkanGraphicsResourceMemoryRegion : public VulkanGraphicsResourceMemoryRegionBase, public GraphicsResourceMemoryRegion<TResource>
    {
        VulkanGraphicsResourceMemoryRegion(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                         std::shared_ptr<VulkanGraphicsResource> owningResource)
            : VulkanGraphicsResourceMemoryRegionBase(GraphicsDevice, owningResource)
        {
        }

        ~GraphicsResourceMemoryRegion() = default;
    };
}