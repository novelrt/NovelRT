// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/OutOfMemoryException.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Utilities/Macros.hpp>

#include <string>
#include <memory>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDeviceObject = GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsMemoryAllocator = GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsResource = GraphicsResource<Vulkan::VulkanGraphicsBackend>;
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsResource> VulkanGraphicsResource::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsResource>(GraphicsDeviceObject::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsResource> VulkanGraphicsResource::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsResource>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsResource::GraphicsResource(std::weak_ptr<VulkanGraphicsDevice> graphicsDevice,
        std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
        GraphicsResourceAccess cpuAccess,
        VmaAllocation allocation,
        VmaAllocationInfo allocationInfo)
        : _device(graphicsDevice)
        , _allocator(allocator)
        , _allocation(allocation)
        , _allocationInfo(allocationInfo)
        , _virtualBlock(VK_NULL_HANDLE)
        , _cpuAccess(cpuAccess)
    {
        VmaVirtualBlockCreateInfo createInfo{};
        createInfo.size = GetSize();

        const VkResult result = vmaCreateVirtualBlock(&createInfo, &_virtualBlock);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create virtual memory block for VkBuffer",
                            std::to_string(result));
        }
    }

    std::weak_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsResource::GetAllocator() const noexcept
    {
        return _allocator;
    }

    GraphicsResourceAccess VulkanGraphicsResource::GetCpuAccess() const noexcept
    {
        return _cpuAccess;
    }

    size_t VulkanGraphicsResource::GetDeviceMemoryOffset() const noexcept
    {
        return _allocationInfo.offset;
    }

    size_t VulkanGraphicsResource::GetSize() const noexcept
    {
        return _allocationInfo.size;
    }

    std::tuple<VmaVirtualAllocation, VmaVirtualAllocationInfo> VulkanGraphicsResource::GetVirtualAllocation(size_t size, size_t alignment)
    {
        VmaVirtualAllocationCreateInfo allocInfo{};
        allocInfo.size = size;
        allocInfo.alignment = alignment;

        VmaVirtualAllocation allocHandle = VK_NULL_HANDLE;
        VkDeviceSize offset{};

        const VkResult allocResult = vmaVirtualAllocate(_virtualBlock, &allocInfo, &allocHandle, &offset);

        if (allocResult != VK_SUCCESS)
        {
            throw Exceptions::OutOfMemoryException("Unable to allocate additional memory in the Vulkan graphics resource.");
        }

        VmaVirtualAllocationInfo allocResultInfo{};
        vmaGetVirtualAllocationInfo(GetVirtualBlock(), allocHandle, &allocResultInfo);

        return std::make_tuple(allocHandle, allocResultInfo);
    }

    std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsResource>> VulkanGraphicsResource::Allocate(size_t size, size_t alignment)
    {
        auto [allocation, info] = GetVirtualAllocation(size, alignment);
        return std::make_shared<VulkanGraphicsResourceMemoryRegion<GraphicsResource>>(GetDevice(), shared_from_this(), allocation, info);
    }

    void VulkanGraphicsResource::Free(VulkanGraphicsResourceMemoryRegion<GraphicsResource>& region)
    {
        vmaVirtualFree(GetVirtualBlock(), region.GetVirtualAllocation());
    }

    VmaAllocation VulkanGraphicsResource::GetAllocation() const noexcept
    {
        return _allocation;
    }

    const VmaAllocationInfo& VulkanGraphicsResource::GetAllocationInfo() const noexcept
    {
        return _allocationInfo;
    }

    VmaVirtualBlock VulkanGraphicsResource::GetVirtualBlock() const noexcept
    {
        return _virtualBlock;
    }
}
