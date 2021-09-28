// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VkDeviceMemory VulkanGraphicsMemoryBlock::CreateVulkanDeviceMemory()
    {
        VkDeviceMemory vulkanDeviceMemory = VK_NULL_HANDLE;

        std::shared_ptr<VulkanGraphicsMemoryBlockCollection> collection = GetCollection();
        VkDevice vulkanDevice = collection->GetAllocator()->GetDevice()->GetVulkanDevice();

        VkMemoryAllocateInfo memoryAllocateInfo{};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = GetSize();
        memoryAllocateInfo.memoryTypeIndex = collection->GetVulkanMemoryTypeIndex();

        VkResult result = vkAllocateMemory(vulkanDevice, &memoryAllocateInfo, nullptr, &vulkanDeviceMemory);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise VkDeviceMemory instance.", result);
        }

        return vulkanDeviceMemory;
    }

    void VulkanGraphicsMemoryBlock::DisposeVulkanDeviceMemory() noexcept
    {
        if (_vulkanDeviceMemory.isCreated())
        {
            vkFreeMemory(GetCollection()->GetAllocator()->GetDevice()->GetVulkanDevice(),
                         _vulkanDeviceMemory.getActual(), nullptr);
        }
    }

    VulkanGraphicsDevice* VulkanGraphicsMemoryBlock::GetDeviceInternal() const noexcept
    {
        return dynamic_cast<VulkanGraphicsDevice*>(GraphicsDeviceObject::GetDevice().get());
    }

    VulkanGraphicsMemoryBlock::VulkanGraphicsMemoryBlock(
        const std::shared_ptr<VulkanGraphicsDevice>& device,
        const std::shared_ptr<VulkanGraphicsMemoryBlockCollection>& collection)
        : GraphicsMemoryBlock(std::static_pointer_cast<GraphicsDevice>(device),
                              std::static_pointer_cast<GraphicsMemoryBlockCollection>(collection)),
          _vulkanDeviceMemory([&]() { return CreateVulkanDeviceMemory(); })
    {
    }

    VulkanGraphicsMemoryBlock::~VulkanGraphicsMemoryBlock()
    {
        DisposeVulkanDeviceMemory();
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
