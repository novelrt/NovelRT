// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VkImageView VulkanGraphicsTexture::CreateVulkanImageView()
    {
        VkImageView vulkanImageView = VK_NULL_HANDLE;

        VulkanGraphicsDevice* device = VulkanGraphicsResource::GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();

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
            throw Exceptions::InitialisationFailureException("Failed to create VkImageView for texture!",
                                                             imageViewResult);
        }

        return vulkanImageView;
    }

    VkSampler VulkanGraphicsTexture::CreateVulkanSampler()
    {
        VkSampler vulkanSampler = VK_NULL_HANDLE;

        VulkanGraphicsDevice* device = VulkanGraphicsResource::GetAllocator()->GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();

        VkSamplerAddressMode addressMode = Utilities::GetVulkanAddressMode(GetAddressMode());

        VkSamplerCreateInfo samplerCreateInfo{};
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerCreateInfo.maxLod = 1.0f;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_WHITE;
        samplerCreateInfo.addressModeU = addressMode;
        samplerCreateInfo.addressModeV = addressMode;
        samplerCreateInfo.addressModeW = addressMode;

        VkResult result = vkCreateSampler(vulkanDevice, &samplerCreateInfo, nullptr, &vulkanSampler);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkSampler!", result);
        }

        return vulkanSampler;
    }

    std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> VulkanGraphicsTexture::AllocateInternal(
        VmaVirtualAllocation allocation,
        VmaVirtualAllocationInfo info)
    {
        return std::make_unique<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsTexture>>(GetDevice(), this, allocation, info);
    }

    void VulkanGraphicsTexture::FreeInternal(VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>& region)
    {
        unused(region);
        // TODO: Not sure if we need to support this, but since we do so for allocation, at least having this for freeing makes sense.
    }

    VulkanGraphicsTexture::VulkanGraphicsTexture(VulkanGraphicsDevice* device,
                                                 VulkanGraphicsMemoryAllocator* allocator,
                                                 GraphicsResourceAccess cpuAccess,
                                                 GraphicsTextureAddressMode addressMode,
                                                 GraphicsTextureKind kind,
                                                 //NOLINTBEGIN(bugprone-easily-swappable-parameters)
                                                 uint32_t width,
                                                 uint32_t height,
                                                 uint16_t depth,
                                                 //NOLINTEND(bugprone-easily-swappable-parameters)
                                                 VmaAllocation allocation,
                                                 VmaAllocationInfo allocationInfo,
                                                 VkImage vulkanImage)
        : VulkanGraphicsResource(device, allocator, cpuAccess, allocation, allocationInfo)
        , _vulkanImage(vulkanImage)
        , _mappedMemoryRegions(0)
        , _addressMode(addressMode)
        , _kind(kind)
        , _vulkanImageView([&]() { return CreateVulkanImageView(); })
        , _vulkanSampler([&]() { return CreateVulkanSampler(); })
        , _width(width)
        , _height(height)
        , _depth(depth)
    {

        VkResult result = vkBindImageMemory(GetDevice()->GetVulkanDevice(), GetVulkanImage(), GetAllocationInfo().deviceMemory, GetAllocationInfo().offset);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to bind VkImage to VkImageMemory correctly.",
                                                             result);
        }
    }

    VulkanGraphicsTexture::~VulkanGraphicsTexture() noexcept
    {
        auto* vulkanDevice = VulkanGraphicsResource::GetDevice()->GetVulkanDevice();
        auto* allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto* allocation = GetAllocation();

        assert_message(_mappedMemoryRegions == 0, "Attempted to destroy a VkImage containing mapped regions.");

        if (_vulkanImageView.HasValue())
        {
            vkDestroyImageView(vulkanDevice, _vulkanImageView.Get(), nullptr);
            _vulkanImageView.Reset();
        }

        if (_vulkanSampler.HasValue())
        {
            vkDestroyImageView(vulkanDevice, _vulkanImageView.Get(), nullptr);
            _vulkanSampler.Reset();
        }

        vmaDestroyImage(allocator, GetVulkanImage(), allocation);
    }

    GraphicsTextureAddressMode VulkanGraphicsTexture::GetAddressMode() const noexcept
    {
        return _addressMode;
    }

    GraphicsTextureKind VulkanGraphicsTexture::GetKind() const noexcept
    {
        return _kind;
    }

    NovelRT::Utilities::Span<uint8_t> VulkanGraphicsTexture::MapBytes(size_t rangeOffset, size_t rangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkTexture that exceeded the VkBuffer's size.");
        }

        void* data = nullptr;
        VkResult result =
            vmaMapMemory(VulkanGraphicsResource::GetAllocator()->GetVmaAllocator(), GetAllocation(), &data);

        if (result != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(result));
        }

        _mappedMemoryRegions++;

        return {reinterpret_cast<uint8_t*>(data) + rangeOffset, rangeLength};
    }

    NovelRT::Utilities::Span<const uint8_t> VulkanGraphicsTexture::MapBytesForRead(size_t rangeOffset,
                                                                                   size_t rangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        VmaAllocator allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        VmaAllocation allocation = GetAllocation();

        void* data = nullptr;
        VkResult mapResult = vmaMapMemory(allocator, allocation, &data);

        if (mapResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(mapResult));
        }

        VkResult invalidateResult = vmaInvalidateAllocation(allocator, allocation, rangeOffset, rangeLength);

        if (invalidateResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to invalidate mapped memory. Reason: " + std::to_string(mapResult));
        }

        _mappedMemoryRegions++;

        return {reinterpret_cast<const uint8_t*>(data), rangeLength};
    }

    void VulkanGraphicsTexture::UnmapBytes()
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of texture when no memory map was created.");
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(VulkanGraphicsResource::GetAllocator()->GetVmaAllocator(), GetAllocation());
    }

    void VulkanGraphicsTexture::UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of texture when no memory map was created.");
        }

        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - writtenRangeOffset;

        if (rangeValidationValue < writtenRangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to write a subrange of a VkImage that exceeded the VkBuffer's size.");
        }

        auto* allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto* allocation = GetAllocation();

        VkResult result = vmaFlushAllocation(allocator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(allocator, allocation);
    }

    VkImage VulkanGraphicsTexture::GetVulkanImage() const noexcept
    {
        return _vulkanImage;
    }

    VkImageView VulkanGraphicsTexture::GetOrCreateVulkanImageView()
    {
        return _vulkanImageView.Get();
    }

    VkSampler VulkanGraphicsTexture::GetOrCreateVulkanSampler()
    {
        return _vulkanSampler.Get();
    }

    uint32_t VulkanGraphicsTexture::GetWidth() const noexcept
    {
        return _width;
    }

    uint32_t VulkanGraphicsTexture::GetHeight() const noexcept
    {
        return _height;
    }

    uint32_t VulkanGraphicsTexture::GetDepth() const noexcept
    {
        return _depth;
    }
}

template class NovelRT::Graphics::GraphicsTexture<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
