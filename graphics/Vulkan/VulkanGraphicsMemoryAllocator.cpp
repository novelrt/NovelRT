// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <vk_mem_alloc.h>
//#include <NovelRT/Graphics/Vulkan/VulkanGraphics

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsMemoryAllocator::VulkanGraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                                                 std::shared_ptr<GraphicsDevice> device)
        : GraphicsMemoryAllocator(provider, device), _allocator(VK_NULL_HANDLE)
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
        return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsDeviceObject::GetDevice());
    }

    std::shared_ptr<VulkanGraphicsProvider> VulkanGraphicsMemoryAllocator::GetProvider() const noexcept
    {
        return std::dynamic_pointer_cast<VulkanGraphicsProvider>(GraphicsMemoryAllocator::GetProvider());
    }

    std::shared_ptr<GraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateBuffer(
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
        VmaAllocationInfo outAllocationInfo{}; //TODO: I haven't figured out what I am doing with this yet, but I'm fairly sure we need it. Lol.

        VkResult result = vmaCreateBuffer(_allocator, &bufferCreateInfo, &allocationCreateInfo, &outBuffer, &outAllocation, &outAllocationInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to correctly initialise the newly requested Vulkan Buffer based on the supplied createInfo object.", result);
        }

        //return std::static_pointer_cast<GraphicsBuffer>(std::make_shared<VulkanGraphicsBuffer>()); //TODO: implement type!
        return nullptr;
    }

    std::shared_ptr<GraphicsTexture> VulkanGraphicsMemoryAllocator::CreateTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        return nullptr;
    }

    std::shared_ptr<VulkanGraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateVulkanBuffer(
        const GraphicsBufferCreateInfo& createInfo)
    {
        return nullptr;
    }

    std::shared_ptr<VulkanGraphicsTexture> VulkanGraphicsMemoryAllocator::CreateVulkanTexture(
        const GraphicsTextureCreateInfo& createInfo)
    {
        return nullptr;
    }
}