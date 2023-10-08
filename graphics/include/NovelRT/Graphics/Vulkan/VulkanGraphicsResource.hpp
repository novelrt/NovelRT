#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <vma/vk_mem_alloc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;

    class VulkanGraphicsResource : public GraphicsResource
    {
    private:
        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;

    public:
        VulkanGraphicsResource(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                               std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                               GraphicsResourceAccess cpuAccess,
                               VmaAllocation allocation,
                               VmaAllocationInfo allocationInfo) noexcept;

        ~VulkanGraphicsResource() noexcept override = default;
        
        [[nodiscard]] std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;

        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept final;

        [[nodiscard]] size_t GetSize() const noexcept final;

        [[nodiscard]] VmaAllocation GetAllocation() const noexcept;

        [[nodiscard]] const VmaAllocationInfo& GetAllocationInfo() const noexcept;
    };
}