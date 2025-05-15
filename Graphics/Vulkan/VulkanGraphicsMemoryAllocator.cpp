// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Texel.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsMemoryAllocator::VulkanGraphicsMemoryAllocator(std::shared_ptr<VulkanGraphicsDevice> device,
                                                                 std::shared_ptr<VulkanGraphicsProvider> provider)
        : _allocator(VK_NULL_HANDLE), _device(device), _provider(provider)
    {
        auto vulkanDevice = GetDevice();
        auto vulkanAdapter = vulkanDevice->GetAdapter();
        auto vulkanProvider = GetProvider();

        VmaAllocatorCreateInfo createInfo{};
        createInfo.vulkanApiVersion = vulkanProvider->GetApiVersion();
        createInfo.physicalDevice = vulkanAdapter->GetVulkanPhysicalDevice();
        createInfo.device = vulkanDevice->GetVulkanDevice();
        createInfo.instance = vulkanProvider->GetVulkanInstance();

        VkResult result = vmaCreateAllocator(&createInfo, &_allocator);

        if (result != VK_SUCCESS)
        {
            Exceptions::InitialisationFailureException("Failed to create the VulkanMemoryAllocator.", result);
        }
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsMemoryAllocator::GetDevice() const noexcept
    {
        return _device;
    }

    std::shared_ptr<VulkanGraphicsProvider> VulkanGraphicsMemoryAllocator::GetProvider() const noexcept
    {
        return _provider;
    }

    std::shared_ptr<VulkanGraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateBuffer(
        const GraphicsBufferCreateInfo& createInfo)
    {
        return CreateVulkanBuffer(createInfo);
    }

    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsMemoryAllocator::CreateTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        return CreateVulkanTexture(createInfo);
    }

    std::shared_ptr<VulkanGraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateVulkanBuffer(
        const GraphicsBufferCreateInfo& createInfo)
    {
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size = createInfo.size;
        bufferCreateInfo.usage = Utilities::GetVulkanBufferUsageKind(createInfo.bufferKind, createInfo.gpuAccessKind);

        VmaAllocationCreateInfo allocationCreateInfo{};
        allocationCreateInfo.flags = Utilities::GetVmaAllocationKind(createInfo.cpuAccessKind);
        allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;

        VkBuffer outBuffer = VK_NULL_HANDLE;
        VmaAllocation outAllocation = VK_NULL_HANDLE;
        VmaAllocationInfo outAllocationInfo{}; // TODO: I haven't figured out what I am doing with this yet, but I'm
                                               // fairly sure we need it. Lol.

        VkResult result = vmaCreateBuffer(GetVmaAllocator(), &bufferCreateInfo, &allocationCreateInfo, &outBuffer,
                                          &outAllocation, &outAllocationInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to correctly initialise the newly requested "
                                                             "Vulkan Buffer based on the supplied createInfo object.",
                                                             result);
        }

        return std::make_shared<VulkanGraphicsBuffer>(GetDevice(), shared_from_this(), createInfo.cpuAccessKind,
                                                      createInfo.bufferKind, outAllocation, outAllocationInfo,
                                                      outBuffer);
    }

    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsMemoryAllocator::CreateVulkanTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        VkImageType imageType{};

        switch (createInfo.textureKind)
        {
            case GraphicsTextureKind::OneDimensional:
                imageType = VK_IMAGE_TYPE_1D;
                break;
            case GraphicsTextureKind::TwoDimensional:
                imageType = VK_IMAGE_TYPE_2D;
                break;
            case GraphicsTextureKind::ThreeDimensional:
                imageType = VK_IMAGE_TYPE_3D;
                break;
            default:
            case GraphicsTextureKind::Unknown:
                throw Exceptions::NotSupportedException(
                    "The specified texture kind is not supported in the default Vulkan pipeline.");
        }

        VkExtent3D extent{};
        extent.width = createInfo.width;
        extent.height = createInfo.height;
        extent.depth = createInfo.depth;

        VkImageCreateInfo imageCreateInfo{};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.imageType = imageType;
        imageCreateInfo.format = Utilities::Map(createInfo.texelFormat);
        imageCreateInfo.extent = extent;
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.usage = Utilities::GetVulkanImageUsageKind(createInfo.textureKind, createInfo.gpuAccessKind);

        VkImage vulkanImage = VK_NULL_HANDLE;
        VmaAllocation outAllocation = VK_NULL_HANDLE;
        VmaAllocationInfo outAllocationInfo{}; // TODO: I haven't figured out what I am doing with this yet, but I'm
                                               // fairly sure we need it. Lol.

        VmaAllocationCreateInfo allocationCreateInfo{};
        allocationCreateInfo.flags = Utilities::GetVmaAllocationKind(createInfo.cpuAccessKind);
        allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
        // allocationCreateInfo.priority = 1; //TODO: do I need this?

        VkResult result = vmaCreateImage(GetVmaAllocator(), &imageCreateInfo, &allocationCreateInfo, &vulkanImage,
                                         &outAllocation, &outAllocationInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to correctly initialise the newly requested "
                                                             "Vulkan Image based on the supplied createInfo object.",
                                                             result);
        }

        return std::make_shared<VulkanGraphicsTexture>(
            GetDevice(), shared_from_this(), createInfo.cpuAccessKind, createInfo.addressMode, createInfo.textureKind,
            createInfo.width, createInfo.height, createInfo.depth, outAllocation, outAllocationInfo, vulkanImage);
    }

    VmaAllocator VulkanGraphicsMemoryAllocator::GetVmaAllocator() const noexcept
    {
        return _allocator;
    }
}
