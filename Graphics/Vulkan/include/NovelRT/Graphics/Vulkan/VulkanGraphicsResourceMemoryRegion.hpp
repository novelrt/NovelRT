#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <vk_mem_alloc.h>

#include <type_traits>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsResource;

    class VulkanGraphicsResourceMemoryRegionBase : public std::enable_shared_from_this<VulkanGraphicsResourceMemoryRegionBase>
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
        VmaVirtualAllocation _virtualAllocation;
        VmaVirtualAllocationInfo _virtualAllocationInfo;

    protected:
        std::shared_ptr<VulkanGraphicsResource> _owningResource;

        VulkanGraphicsResourceMemoryRegionBase(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                           std::shared_ptr<VulkanGraphicsResource> owningResource,
                                           VmaVirtualAllocation virtualAllocation,
                                           VmaVirtualAllocationInfo virtualAllocationInfo);

    public:
        ~VulkanGraphicsResourceMemoryRegionBase() = default;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;

        [[nodiscard]] size_t GetOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] VmaVirtualAllocation GetVirtualAllocation() const noexcept;

        [[nodiscard]] VmaVirtualAllocationInfo GetVirtualAllocationInfo() const noexcept;
    };

    template<typename TResource>
    class VulkanGraphicsResourceMemoryRegion
        : public std::conditional_t<std::is_same_v<TResource, VulkanGraphicsResource>, VulkanGraphicsResourceMemoryRegionBase, VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>>
    {
    private:
        using Super = std::conditional_t<std::is_same_v<TResource, VulkanGraphicsResource>, VulkanGraphicsResourceMemoryRegionBase, VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>>;
    public:
        VulkanGraphicsResourceMemoryRegion(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                         std::shared_ptr<TResource> owningResource,
                                         VmaVirtualAllocation virtualAllocation,
                                           VmaVirtualAllocationInfo virtualAllocationInfo)
            : Super(graphicsDevice, owningResource, virtualAllocation, virtualAllocationInfo)
        {
        }

        [[nodiscard]] std::shared_ptr<TResource> GetOwningResource() const noexcept
        {
            return std::static_pointer_cast<TResource>(VulkanGraphicsResourceMemoryRegionBase::_owningResource);
        }

        ~VulkanGraphicsResourceMemoryRegion() = default;
    };
}
