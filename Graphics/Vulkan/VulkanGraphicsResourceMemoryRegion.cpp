// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::VulkanGraphicsResourceMemoryRegion(
        VulkanGraphicsDevice* graphicsDevice,
        VulkanGraphicsResource* owningResource,
        VmaVirtualAllocation virtualAllocation,
        VmaVirtualAllocationInfo virtualAllocationInfo)
        : _device(graphicsDevice)
        ,  _owningResource(owningResource)
        ,  _virtualAllocation(virtualAllocation)
        ,  _virtualAllocationInfo(virtualAllocationInfo)
    {
        if (_virtualAllocation == VK_NULL_HANDLE || _virtualAllocationInfo.size == 0)
        {
            throw Exceptions::InitialisationFailureException(
                "An invalid memory region of a Vulkan graphics resource was created.");
        }
    }

    VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::~VulkanGraphicsResourceMemoryRegion()
    {
        _owningResource->Free(*this);
    }

    size_t VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::GetOffset() const noexcept
    {
        return _virtualAllocationInfo.offset;
    }

    size_t VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::GetSize() const noexcept
    {
        return _virtualAllocationInfo.size;
    }

    VmaVirtualAllocation VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::GetVirtualAllocation() const noexcept
    {
        return _virtualAllocation;
    }

    VmaVirtualAllocationInfo VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::GetVirtualAllocationInfo() const noexcept
    {
        return _virtualAllocationInfo;
    }
}

template class NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::GraphicsResource, NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
