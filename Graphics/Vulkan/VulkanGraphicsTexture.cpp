// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDeviceObject = GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsMemoryAllocator = GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsResource = GraphicsResource<Vulkan::VulkanGraphicsBackend>;
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;

    VkImageView CreateVulkanImageView(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        GraphicsTextureKind kind,
        VkImage image)
    {
        VkImageViewType viewType;
        switch (kind)
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
        imageViewCreateInfo.image = image;
        imageViewCreateInfo.viewType = viewType;
        imageViewCreateInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageViewCreateInfo.components = components;
        imageViewCreateInfo.subresourceRange = subresourceRange;

        VkImageView vulkanImageView = VK_NULL_HANDLE;
        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkResult imageViewResult = vkCreateImageView(vulkanDevice, &imageViewCreateInfo, nullptr, &vulkanImageView);

        if (imageViewResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkImageView for texture!",
                                                             imageViewResult);
        }

        return vulkanImageView;
    }

    VkSampler CreateVulkanSampler(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        GraphicsTextureAddressMode addressMode)
    {
        VkSamplerCreateInfo samplerCreateInfo{};
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerCreateInfo.maxLod = 1.0f;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_WHITE;

        VkSamplerAddressMode vkAddressMode = Vulkan::Utilities::GetVulkanAddressMode(addressMode);
        samplerCreateInfo.addressModeU = vkAddressMode;
        samplerCreateInfo.addressModeV = vkAddressMode;
        samplerCreateInfo.addressModeW = vkAddressMode;

        VkSampler vulkanSampler = VK_NULL_HANDLE;
        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkResult result = vkCreateSampler(vulkanDevice, &samplerCreateInfo, nullptr, &vulkanSampler);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkSampler!", result);
        }

        return vulkanSampler;
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsTexture::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsTexture>(GraphicsResource::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsTexture> VulkanGraphicsTexture::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsTexture>(GraphicsResource::shared_from_this());
    }

    VulkanGraphicsTexture::GraphicsTexture(
        std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
        std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
        const GraphicsTextureCreateInfo& createInfo,
        VmaAllocation allocation,
        VmaAllocationInfo allocationInfo,
        VkImage vulkanImage)
        : VulkanGraphicsResource(std::move(graphicsDevice), std::move(allocator), createInfo.cpuAccessKind, allocation, allocationInfo)
        , _vulkanImage(vulkanImage)
        , _mappedMemoryRegions(0)
        , _addressMode(createInfo.addressMode)
        , _kind(createInfo.textureKind)
        , _vulkanImageView([device = GetDevice(), textureKind = createInfo.textureKind, vulkanImage]() { return CreateVulkanImageView(device, textureKind, vulkanImage); })
        , _vulkanSampler([device = GetDevice(), addressMode = createInfo.addressMode]() { return CreateVulkanSampler(device, addressMode); })
        , _width(createInfo.width)
        , _height(createInfo.height)
        , _depth(createInfo.depth)
    {

        auto device = GetDevice();
        VkResult result = vkBindImageMemory(device->GetVulkanDevice(), vulkanImage, allocationInfo.deviceMemory, allocationInfo.offset);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to bind VkImage to VkImageMemory correctly.",
                                                             result);
        }
    }

    VulkanGraphicsTexture::~GraphicsTexture() noexcept
    {
        assert_message(_mappedMemoryRegions == 0, "Attempted to destroy a VkImage containing mapped regions.");

        auto device = GetDevice();
        auto vulkanDevice = device->GetVulkanDevice();

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

        auto allocator = GetAllocator();
        auto vmaAllocator = allocator->GetVmaAllocator();
        auto allocation = GetAllocation();
        vmaDestroyImage(vmaAllocator, _vulkanImage, allocation);
    }

    std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsTexture>> VulkanGraphicsTexture::Allocate(size_t size, size_t alignment)
    {
        auto [allocation, info] = GetVirtualAllocation(size, alignment);
        return std::make_shared<VulkanGraphicsResourceMemoryRegion<GraphicsTexture>>(GetDevice(), shared_from_this(), allocation, info);
    }

    void VulkanGraphicsTexture::Free(VulkanGraphicsResourceMemoryRegion<GraphicsTexture>& region)
    {
        VulkanGraphicsResource::Free(region);
    }

    GraphicsTextureAddressMode VulkanGraphicsTexture::GetAddressMode() const noexcept
    {
        return _addressMode;
    }

    GraphicsTextureKind VulkanGraphicsTexture::GetKind() const noexcept
    {
        return _kind;
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

    NovelRT::Utilities::Span<uint8_t> VulkanGraphicsTexture::MapBytes(size_t rangeOffset, size_t rangeLength)
    {
        static_assert(
            std::is_same_v<uint8_t, char> || std::is_same_v<uint8_t, unsigned char> || std::is_same_v<uint8_t, std::byte>,
            "uint8_t must be able to access the object representation of the byte buffer");

        size_t sizeOfBuffer = static_cast<size_t>(GetAllocationInfo().size);
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkTexture that exceeded the VkBuffer's size.");
        }

        void* data = nullptr;
        auto allocator = GetAllocator();
        VkResult result = vmaMapMemory(allocator->GetVmaAllocator(), GetAllocation(), &data);

        if (result != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(result));
        }

        _mappedMemoryRegions++;

        return {static_cast<uint8_t*>(data) + rangeOffset, rangeLength};
    }

    NovelRT::Utilities::Span<const uint8_t> VulkanGraphicsTexture::MapBytesForRead(size_t rangeOffset, size_t rangeLength)
    {
        static_assert(
            std::is_same_v<uint8_t, char> || std::is_same_v<uint8_t, unsigned char> || std::is_same_v<uint8_t, std::byte>,
            "uint8_t must be able to access the object representation of the byte buffer");

        size_t sizeOfBuffer = static_cast<size_t>(GetAllocationInfo().size);
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        void* data = nullptr;
        auto allocator = GetAllocator();
        auto vmaAllocator = allocator->GetVmaAllocator();
        auto allocation = GetAllocation();
        VkResult mapResult = vmaMapMemory(vmaAllocator, allocation, &data);

        if (mapResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(mapResult));
        }

        VkResult invalidateResult = vmaInvalidateAllocation(vmaAllocator, allocation, rangeOffset, rangeLength);

        if (invalidateResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to invalidate mapped memory. Reason: " + std::to_string(mapResult));
        }

        _mappedMemoryRegions++;

        return {static_cast<const uint8_t*>(data), rangeLength};
    }

    void VulkanGraphicsTexture::UnmapBytes()
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of texture when no memory map was created.");
        }

        _mappedMemoryRegions--;

        auto allocator = GetAllocator();
        vmaUnmapMemory(allocator->GetVmaAllocator(), GetAllocation());
    }

    void VulkanGraphicsTexture::UnmapBytesAndWrite()
    {
        auto allocationInfo = GetAllocationInfo();
        UnmapBytesAndWrite(static_cast<size_t>(allocationInfo.offset), static_cast<size_t>(allocationInfo.size));
    }

    void VulkanGraphicsTexture::UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of texture when no memory map was created.");
        }

        size_t sizeOfBuffer = static_cast<size_t>(GetAllocationInfo().size);
        size_t rangeValidationValue = sizeOfBuffer - writtenRangeOffset;

        if (rangeValidationValue < writtenRangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to write a subrange of a VkImage that exceeded the VkBuffer's size.");
        }

        auto allocator = GetAllocator();
        auto vmaAllcoator = allocator->GetVmaAllocator();
        auto allocation = GetAllocation();

        VkResult result = vmaFlushAllocation(vmaAllcoator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(vmaAllcoator, allocation);
    }

    void VulkanGraphicsTexture::UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsTexture, Vulkan::VulkanGraphicsBackend>* memoryRegion)
    {
        return UnmapBytesAndWrite(memoryRegion->GetOffset(), memoryRegion->GetSize());
    }

    VkImage VulkanGraphicsTexture::GetVulkanImage() const noexcept
    {
        return _vulkanImage;
    }

    VkImageView VulkanGraphicsTexture::GetVulkanImageView() const
    {
        return _vulkanImageView.Get();
    }

    VkSampler VulkanGraphicsTexture::GetVulkanSampler() const
    {
        return _vulkanSampler.Get();
    }
}
