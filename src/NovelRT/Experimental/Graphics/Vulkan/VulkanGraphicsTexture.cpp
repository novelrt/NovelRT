// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanGraphicsTexture.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VulkanGraphicsTexture::VulkanGraphicsTexture(std::shared_ptr<VulkanGraphicsDevice> device,
                                                 GraphicsTextureKind kind,
                                                 GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                                                 GraphicsResourceCpuAccessKind cpuAccess,
                                                 uint32_t width,
                                                 uint32_t height,
                                                 uint16_t depth,
                                                 VkImage vulkanImage)
        : GraphicsTexture(std::move(device), kind, std::move(blockRegion), cpuAccess, width, height, depth),
          _vulkanImageView([&]() { return CreateVulkanImageView(); }),
          _vulkanSampler([&]() { return CreateVulkanSampler(); }),
          _vulkanImage(vulkanImage)
    {
        VkResult result = vkBindImageMemory(GetAllocator()->GetDevice()->GetVulkanDevice(), vulkanImage,
                                            GetBlock()->GetVulkanDeviceMemory(), GetBlockRegion().GetOffset());

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to bind VkImage to VkImageMemory correctly.",
                                                             result);
        }
    }

    void* Vulkan::VulkanGraphicsTexture::MapUntyped()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;
        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to map VkMemory to T*! Reason: " + std::to_string(mapMemoryResult));
        }

        return pDestination;
    }

    void* VulkanGraphicsTexture::MapUntyped(size_t rangeOffset, size_t /*rangeLength*/)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;

        VkResult result = vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to map VkDeviceMemory! Reason: " + std::to_string(result));
        }

        return reinterpret_cast<uint8_t*>(pDestination) + rangeOffset;
    }

    const void* VulkanGraphicsTexture::MapForReadUntyped()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;
        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Add real exception.
            throw std::runtime_error("Failed to map VkMemory to T*! Reason: " + std::to_string(mapMemoryResult));
        }

        size_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;
        size_t offset = GetOffset();
        size_t size = (GetSize() + nonCoherentAtomSize - 1) & ~(nonCoherentAtomSize - 1);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult invalidateResult = vkInvalidateMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

        if (invalidateResult != VK_SUCCESS)
        {
            // TODO: Add real exception.
            throw std::runtime_error("Failed to invalidate memory ranges to prevent writing! Reason: " +
                                     std::to_string(invalidateResult));
        }

        return pDestination;
    }

    const void* VulkanGraphicsTexture::MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;
        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Add real exception.
            throw std::runtime_error("Failed to map VkMemory to T*! Reason: " + std::to_string(mapMemoryResult));
        }

        if (readRangeLength != 0)
        {
            size_t nonCoherentAtomSize =
                device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;
            size_t offset = GetOffset() + readRangeOffset;
            size_t size = (readRangeLength + nonCoherentAtomSize - 1) & ~(nonCoherentAtomSize - 1);

            VkMappedMemoryRange mappedMemoryRange{};
            mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
            mappedMemoryRange.memory = vulkanDeviceMemory;
            mappedMemoryRange.offset = offset;
            mappedMemoryRange.size = size;

            VkResult invalidateResult = vkInvalidateMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

            if (invalidateResult != VK_SUCCESS)
            {
                // TODO: Add real exception.
                throw std::runtime_error("Failed to invalidate memory ranges to prevent writing! Reason: " +
                                         std::to_string(invalidateResult));
            }
        }

        return reinterpret_cast<uint8_t*>(pDestination) + readRangeOffset;
    }

    void VulkanGraphicsTexture::Unmap()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    void VulkanGraphicsTexture::UnmapAndWrite()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        size_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;
        size_t offset = GetOffset();
        size_t size = (GetSize() + nonCoherentAtomSize - 1) & ~(nonCoherentAtomSize - 1);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult flushResult = vkFlushMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

        if (flushResult != VK_SUCCESS)
        {
            // TODO: Add real exception.
            throw std::runtime_error("Failed to flush memory ranges after writing! Reason: " +
                                     std::to_string(flushResult));
        }

        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    void VulkanGraphicsTexture::UnmapAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        if (writtenRangeLength != 0)
        {
            size_t nonCoherentAtomSize =
                device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;
            size_t offset = GetOffset() + writtenRangeOffset;
            size_t size = (writtenRangeLength + nonCoherentAtomSize - 1) & ~(nonCoherentAtomSize - 1);

            VkMappedMemoryRange mappedMemoryRange{};
            mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
            mappedMemoryRange.memory = vulkanDeviceMemory;
            mappedMemoryRange.offset = offset;
            mappedMemoryRange.size = size;

            VkResult flushResult = vkFlushMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

            if (flushResult != VK_SUCCESS)
            {
                // TODO: Add real exception.
                throw std::runtime_error("Failed to flush memory ranges after writing! Reason: " +
                                         std::to_string(flushResult));
            }
        }
        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    VulkanGraphicsTexture::~VulkanGraphicsTexture()
    {
        DisposeVulkanSampler();
        DisposeVulkanImage();
        DisposeVulkanImageView();
        GetBlockRegion().GetCollection()->Free(GetBlockRegion());
    }

    VulkanGraphicsDevice* VulkanGraphicsTexture::GetDeviceInternal() const noexcept
    {
        // TODO: This feels like it might be a perf issue later.
        return dynamic_cast<VulkanGraphicsDevice*>(GraphicsDeviceObject::GetDevice().get());
    }

    VkImageView VulkanGraphicsTexture::CreateVulkanImageView()
    {
        VkImageView vulkanImageView = VK_NULL_HANDLE;

        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        //VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        VkImageViewType viewType;
        switch (GetKind())
        {
            case GraphicsTextureKind::OneDimensional:
                viewType = VK_IMAGE_VIEW_TYPE_1D;
                break;
            case GraphicsTextureKind::TwoDimensional:
                viewType = VK_IMAGE_VIEW_TYPE_2D;
                break;
            case GraphicsTextureKind::ThreeDimensional:
                viewType = VK_IMAGE_VIEW_TYPE_3D;
                break;
            default:
            case GraphicsTextureKind::Unknown:
                throw Exceptions::InvalidOperationException("Invalid or unknown graphics texture kind type specified.");
                break;
        }

        VkComponentMapping components{};
        components.r = VK_COMPONENT_SWIZZLE_R;
        components.g = VK_COMPONENT_SWIZZLE_G;
        components.b = VK_COMPONENT_SWIZZLE_B;
        components.a = VK_COMPONENT_SWIZZLE_A;

        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = GetVulkanImage();
        imageViewCreateInfo.viewType = viewType;
        imageViewCreateInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageViewCreateInfo.components = components;
        imageViewCreateInfo.subresourceRange = subresourceRange;

        VkResult imageViewResult = vkCreateImageView(vulkanDevice, &imageViewCreateInfo, nullptr, &vulkanImageView);

        if (imageViewResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkImageView for texture!", imageViewResult);
        }

        return vulkanImageView;
    }

    VkSampler VulkanGraphicsTexture::CreateVulkanSampler()
    {
        VkSampler vulkanSampler = VK_NULL_HANDLE;

        std::shared_ptr<VulkanGraphicsDevice> device = GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        //VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        VkSamplerCreateInfo samplerCreateInfo{};
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerCreateInfo.maxLod = 1.0f;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_WHITE;

        VkResult result = vkCreateSampler(vulkanDevice, &samplerCreateInfo, nullptr, &vulkanSampler);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkSampler!", result);
        }

        return vulkanSampler;
    }

    void VulkanGraphicsTexture::DisposeVulkanImage() noexcept
    {
        if (_vulkanImage != VK_NULL_HANDLE)
        {
            vkDestroyImage(GetAllocator()->GetDevice()->GetVulkanDevice(), _vulkanImage, nullptr);
        }
    }

    void VulkanGraphicsTexture::DisposeVulkanImageView() noexcept
    {
        if (_vulkanImageView.isCreated())
        {
            vkDestroyImageView(GetAllocator()->GetDevice()->GetVulkanDevice(), _vulkanImageView.getActual(), nullptr);
            _vulkanImageView.reset();
        }
    }

    void VulkanGraphicsTexture::DisposeVulkanSampler() noexcept
    {
        if (_vulkanSampler.isCreated())
        {
            vkDestroySampler(GetAllocator()->GetDevice()->GetVulkanDevice(), _vulkanSampler.getActual(), nullptr);
            _vulkanSampler.reset();
        }
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan