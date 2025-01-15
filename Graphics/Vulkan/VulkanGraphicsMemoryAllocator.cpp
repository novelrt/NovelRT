// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsMemoryAllocator::VulkanGraphicsMemoryAllocator(std::shared_ptr<VulkanGraphicsProvider> provider,
                                                                 std::shared_ptr<VulkanGraphicsDevice> device)
        : _allocator(VK_NULL_HANDLE), _provider(provider), _device(device)
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
        bufferCreateInfo.size = createInfo.size;
        bufferCreateInfo.usage = Utilities::GetVulkanBufferUsageKind(createInfo.bufferKind, createInfo.gpuAccessKind);

        VmaAllocationCreateInfo allocationCreateInfo{};
        allocationCreateInfo.flags = Utilities::GetVmaAllocationKind(createInfo.cpuAccessKind);
        allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;

        VkBuffer outBuffer = VK_NULL_HANDLE;
        VmaAllocation outAllocation = VK_NULL_HANDLE;
        VmaAllocationInfo outAllocationInfo{}; // TODO: I haven't figured out what I am doing with this yet, but I'm
                                               // fairly sure we need it. Lol.

        VkResult result = vmaCreateBuffer(_allocator, &bufferCreateInfo, &allocationCreateInfo, &outBuffer,
                                          &outAllocation, &outAllocationInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to correctly initialise the newly requested "
                                                             "Vulkan Buffer based on the supplied createInfo object.",
                                                             result);
        }

        //return std::make_shared<VulkanGraphicsBuffer>();
        //TODO: unfuck this
        return nullptr;
    }

    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsMemoryAllocator::CreateVulkanTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        //TODO: this
        unused(createInfo);
        return nullptr;
    }

    VmaAllocator VulkanGraphicsMemoryAllocator::GetVmaAllocator() const noexcept
    {
        return _allocator;
    }
}
