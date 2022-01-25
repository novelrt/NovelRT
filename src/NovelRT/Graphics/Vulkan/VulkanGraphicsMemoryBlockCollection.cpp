// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsMemoryBlock* VulkanGraphicsMemoryBlockCollection::CreateBlock(size_t size)
    {
        const GraphicsMemoryAllocatorSettings& settings = GetAllocator()->GetSettings();

        if (!settings.BlockCreationLogicDelegate.has_value())
        {
            throw Exceptions::NotSupportedException(
                "No memory block creation method has been specified for the default Vulkan render pipeline.");
        }

        return reinterpret_cast<VulkanGraphicsMemoryBlock*>(settings.BlockCreationLogicDelegate.value()(
            GetDevice(), std::static_pointer_cast<GraphicsMemoryBlockCollection>(shared_from_this()), size));
    }

    VulkanGraphicsMemoryBlockCollection::VulkanGraphicsMemoryBlockCollection(
        std::shared_ptr<VulkanGraphicsDevice> device,
        std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
        uint32_t memoryTypeIndex)
        : GraphicsMemoryBlockCollection(std::move(device), std::move(allocator)),
          _vulkanMemoryTypeIndex(memoryTypeIndex)
    {
    }
} // namespace NovelRT::Graphics::Vulkan
