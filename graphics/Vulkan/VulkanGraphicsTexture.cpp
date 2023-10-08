// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VkImageView VulkanGraphicsTexture::CreateVulkanImageView()
    {
        VkImageView vulkanImageView = VK_NULL_HANDLE;

        std::shared_ptr<VulkanGraphicsDevice> device = VulkanGraphicsResource::GetAllocator()->GetDevice();

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

        std::shared_ptr<VulkanGraphicsDevice> device = VulkanGraphicsResource::GetAllocator()->GetDevice();

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

    VulkanGraphicsTexture::VulkanGraphicsTexture(std::shared_ptr<VulkanGraphicsDevice> device,
                                                 std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                                                 GraphicsResourceAccess cpuAccess,
                                                 GraphicsTextureAddressMode addressMode,
                                                 GraphicsTextureKind kind,
                                                 uint32_t width,
                                                 uint32_t height,
                                                 uint16_t depth,
                                                 VmaAllocation allocation,
                                                 VmaAllocationInfo allocationInfo,
                                                 size_t subAllocations,
                                                 VkImage vulkanImage)
        : VulkanGraphicsResource(device, allocator, cpuAccess, allocation, allocationInfo),
          GraphicsTexture(device, allocator, cpuAccess, addressMode, kind, width, height, depth),
          _vulkanImage(vulkanImage),
          _subAllocations(0),
          _vulkanImageView([&]() { return CreateVulkanImageView(); }),
          _vulkanSampler([&]() { return CreateVulkanSampler(); })
    {
    }

    VulkanGraphicsTexture::~VulkanGraphicsTexture() noexcept
    {
        auto vulkanDevice = VulkanGraphicsResource::GetDevice()->GetVulkanDevice();
        auto allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto allocation = GetAllocation();

        assert_message(_subAllocations != 0, "Attempted to destroy a VkImage containing mapped regions.");

        if (_vulkanImageView.isCreated())
        {
            vkDestroyImageView(vulkanDevice, _vulkanImageView.getActual(), nullptr);
            _vulkanImageView.reset();
        }

        if (_vulkanSampler.isCreated())
        {
            vkDestroyImageView(vulkanDevice, _vulkanImageView.getActual(), nullptr);
            _vulkanSampler.reset();
        }

        vmaDestroyImage(allocator, GetVulkanImage(), allocation);
    }

    NovelRT::Utilities::Misc::Span<uint8_t> VulkanGraphicsTexture::MapBytes(size_t rangeOffset, size_t rangeLength)
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

        _subAllocations++;

        return NovelRT::Utilities::Misc::Span<uint8_t>(reinterpret_cast<uint8_t*>(data) + rangeOffset, rangeLength);
    }

    NovelRT::Utilities::Misc::Span<const uint8_t> VulkanGraphicsTexture::MapBytesForRead(size_t rangeOffset, size_t rangeLength)
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

        return NovelRT::Utilities::Misc::Span<const uint8_t>(reinterpret_cast<const uint8_t*>(data), rangeLength);
    }

    void VulkanGraphicsTexture::UnmapBytes()
    {
        vmaUnmapMemory(VulkanGraphicsResource::GetAllocator()->GetVmaAllocator(), GetAllocation());
    }

    void VulkanGraphicsTexture::UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - writtenRangeOffset;

        if (rangeValidationValue < writtenRangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to write a subrange of a VkImage that exceeded the VkBuffer's size.");
        }

        auto allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto allocation = GetAllocation();

        VkResult result = vmaFlushAllocation(allocator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        vmaUnmapMemory(allocator, allocation);
    }

    VkImage VulkanGraphicsTexture::GetVulkanImage() const noexcept
    {
        return _vulkanImage;
    }

    VkImageView VulkanGraphicsTexture::GetOrCreateVulkanImageView()
    {
        return _vulkanImageView.getActual();
    }

    VkSampler VulkanGraphicsTexture::GetOrCreateVulkanSampler()
    {
        return _vulkanSampler.getActual();
    }
}