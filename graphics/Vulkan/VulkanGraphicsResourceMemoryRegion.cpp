// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsResourceMemoryRegionBase::VulkanGraphicsResourceMemoryRegionBase(
        std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
        std::shared_ptr<VulkanGraphicsResource> owningResource,
        VmaVirtualAllocation virtualAllocation,
        VmaVirtualAllocationInfo virtualAllocationInfo)
        : GraphicsResourceMemoryRegionBase(graphicsDevice, owningResource),
          _virtualAllocation(virtualAllocation),
          _virtualAllocationInfo(virtualAllocationInfo)
    {
        if (_virtualAllocation == VK_NULL_HANDLE || _virtualAllocationInfo.size == 0)
        {
            throw Exceptions::InitialisationFailureException(
                "An invalid memory region of a Vulkan graphics resource was created.");
        }
    }

    size_t VulkanGraphicsResourceMemoryRegionBase::GetRelativeOffset() const noexcept
    {
        return _virtualAllocationInfo.offset;
    }

    size_t VulkanGraphicsResourceMemoryRegionBase::GetSize() const noexcept
    {
        return _virtualAllocationInfo.size;
    }

    VmaVirtualAllocation VulkanGraphicsResourceMemoryRegionBase::GetVirtualAllocation() const noexcept
    {
        return _virtualAllocation;
    }

    VmaVirtualAllocationInfo VulkanGraphicsResourceMemoryRegionBase::GetVirtualAllocationInfo() const noexcept
    {
        return _virtualAllocationInfo;
    }
}