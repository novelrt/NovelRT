// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDeviceObject = GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsMemoryAllocator = GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsResource = GraphicsResource<Vulkan::VulkanGraphicsBackend>;
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsResource>> VulkanGraphicsResourceMemoryRegion<GraphicsResource>::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsResourceMemoryRegion<GraphicsResource>>(GraphicsDeviceObject::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsResourceMemoryRegion<GraphicsResource>> VulkanGraphicsResourceMemoryRegion<GraphicsResource>::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsResourceMemoryRegion<GraphicsResource>>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GraphicsResourceMemoryRegion(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
        std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> owningResource,
        VmaVirtualAllocation virtualAllocation,
        VmaVirtualAllocationInfo virtualAllocationInfo)
        : _device(std::move(graphicsDevice))
        ,  _owningResource(std::move(owningResource))
        ,  _virtualAllocation(virtualAllocation)
        ,  _virtualAllocationInfo(virtualAllocationInfo)
    {
        if (_virtualAllocation == VK_NULL_HANDLE || _virtualAllocationInfo.size == 0)
        {
            throw Exceptions::InitialisationFailureException(
                "An invalid memory region of a Vulkan graphics resource was created.");
        }
    }

    VulkanGraphicsResourceMemoryRegion<GraphicsResource>::~GraphicsResourceMemoryRegion()
    {
        _owningResource->Free(*this);
    }

    std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GetOwningResource() const noexcept
    {
        return _owningResource;

    }

    size_t VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GetOffset() const noexcept
    {
        return static_cast<size_t>(_virtualAllocationInfo.offset);
    }

    size_t VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GetSize() const noexcept
    {
        return static_cast<size_t>(_virtualAllocationInfo.size);
    }

    VmaVirtualAllocation VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GetVirtualAllocation() const noexcept
    {
        return _virtualAllocation;
    }

    VmaVirtualAllocationInfo VulkanGraphicsResourceMemoryRegion<GraphicsResource>::GetVirtualAllocationInfo() const noexcept
    {
        return _virtualAllocationInfo;
    }
}
