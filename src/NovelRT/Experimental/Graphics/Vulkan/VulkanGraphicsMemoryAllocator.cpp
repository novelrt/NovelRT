// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    // TODO: I have no idea if this works. Lol.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    size_t VulkanGraphicsMemoryAllocator::GetBlockCollectionIndex(GraphicsResourceAccess cpuAccess,
                                                                  uint32_t memoryTypeBits)
    {
        bool isIntegratedGpu = GetDevice()->GetAdapter()->GetVulkanPhysicalDeviceProperties().deviceType ==
                               VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;

        VkMemoryPropertyFlagBits requiredMemoryPropertyFlags = static_cast<VkMemoryPropertyFlagBits>(0);
        VkMemoryPropertyFlagBits preferredMemoryPropertyFlags = static_cast<VkMemoryPropertyFlagBits>(0);
        VkMemoryPropertyFlagBits unpreferredMemoryPropertyFlags = static_cast<VkMemoryPropertyFlagBits>(0);

        switch (cpuAccess)
        {
            case GraphicsResourceAccess::Read:
                requiredMemoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
                preferredMemoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
                break;
            case GraphicsResourceAccess::Write:
                requiredMemoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
                preferredMemoryPropertyFlags |=
                    isIntegratedGpu ? static_cast<VkMemoryPropertyFlagBits>(0) : VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
                break;
            case GraphicsResourceAccess::ReadWrite:
                requiredMemoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
                preferredMemoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
                preferredMemoryPropertyFlags |=
                    isIntegratedGpu ? static_cast<VkMemoryPropertyFlagBits>(0) : VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
                break;
            default:
            case GraphicsResourceAccess::None:
                preferredMemoryPropertyFlags |=
                    isIntegratedGpu ? static_cast<VkMemoryPropertyFlagBits>(0) : VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
                break;
        }

        int32_t index = -1;
        int32_t lowestCost = std::numeric_limits<int32_t>::max();

        const VkPhysicalDeviceMemoryProperties& memoryProperties =
            GetDevice()->GetAdapter()->GetVulkanPhysicalDeviceMemoryProperties();

        for (int32_t i = 0; i < static_cast<int32_t>(_blockCollections.getActual().size()); i++)
        {
            if ((memoryTypeBits & (1 << i)) == 0)
            {
                continue;
            }

            VkMemoryPropertyFlags memoryPropertyFlags = memoryProperties.memoryTypes[i].propertyFlags;

            if ((requiredMemoryPropertyFlags & memoryPropertyFlags) !=
                static_cast<VkMemoryPropertyFlags>(requiredMemoryPropertyFlags))
            {
                continue;
            }

            if (memoryProperties.memoryHeaps[memoryProperties.memoryTypes[i].heapIndex].flags &
                VK_MEMORY_HEAP_MULTI_INSTANCE_BIT)
            {
                continue;
            }

            int32_t cost =
                Maths::Utilities::PopCount(static_cast<uint32_t>(preferredMemoryPropertyFlags) & ~memoryPropertyFlags) +
                Maths::Utilities::PopCount(static_cast<uint32_t>(unpreferredMemoryPropertyFlags) &
                                           ~memoryPropertyFlags);

            if (cost >= lowestCost)
            {
                continue;
            }

            index = i;

            if (cost == 0)
            {
                break;
            }

            lowestCost = cost;
        }

        if (index == -1)
        {
            throw std::out_of_range("Requested memory type unavailable on this physical device.");
        }

        return index;
    }
#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

    VulkanGraphicsMemoryAllocator::VulkanGraphicsMemoryAllocator(std::shared_ptr<VulkanGraphicsDevice> device,
                                                                 GraphicsMemoryAllocatorSettings settings)
        : GraphicsMemoryAllocatorImpl<IGraphicsMemoryRegionCollection<GraphicsResource>::DefaultMetadata>(
              std::move(device),
              std::move(settings)),
          _blockCollections([&]() {
              std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>> returnVec{};
              uint32_t memoryTypeCount =
                  GetDevice()->GetAdapter()->GetVulkanPhysicalDeviceMemoryProperties().memoryTypeCount;
              returnVec.reserve(memoryTypeCount);

              for (uint32_t memoryTypeIndex = 0; memoryTypeIndex < memoryTypeCount; memoryTypeIndex++)
              {
                  returnVec.emplace_back(std::static_pointer_cast<GraphicsMemoryBlockCollection>(
                      std::make_shared<VulkanGraphicsMemoryBlockCollection>(
                          GetDevice(), std::dynamic_pointer_cast<VulkanGraphicsMemoryAllocator>(shared_from_this()),
                          memoryTypeIndex)));
              }

              return returnVec;
          })
    {
        if (!_settings.BlockCreationLogicDelegate.has_value())
        {
            _settings.BlockCreationLogicDelegate = std::function<GraphicsMemoryBlock*(
                std::shared_ptr<GraphicsDevice>, std::shared_ptr<GraphicsMemoryBlockCollection>, size_t)>(
                [](auto device, auto collection, auto size) {
                    return new VulkanGraphicsMemoryBlockImpl<
                        IGraphicsMemoryRegionCollection<GraphicsMemoryBlock>::DefaultMetadata>(
                        std::dynamic_pointer_cast<VulkanGraphicsDevice>(device),
                        std::dynamic_pointer_cast<VulkanGraphicsMemoryBlockCollection>(collection), size);
                });
        }
    }

    std::shared_ptr<GraphicsBuffer> VulkanGraphicsMemoryAllocator::CreateBuffer(
        GraphicsBufferKind bufferKind,
        GraphicsResourceAccess cpuAccessKind,
        GraphicsResourceAccess gpuAccessKind,
        size_t size,
        GraphicsMemoryRegionAllocationFlags allocationFlags)
    {
        VkDevice vulkanDevice = GetDevice()->GetVulkanDevice();

        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size = size;
        bufferCreateInfo.usage = Utilities::GetVulkanBufferUsageKind(bufferKind, gpuAccessKind);

        VkBuffer vulkanBuffer = VK_NULL_HANDLE;

        VkResult bufferCreationResult = vkCreateBuffer(vulkanDevice, &bufferCreateInfo, nullptr, &vulkanBuffer);
        if (bufferCreationResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create requested VkBuffer instance.",
                                                             bufferCreationResult);
        }

        VkMemoryRequirements memoryRequirements{};
        vkGetBufferMemoryRequirements(vulkanDevice, vulkanBuffer, &memoryRequirements);

        size_t index = GetBlockCollectionIndex(cpuAccessKind, memoryRequirements.memoryTypeBits);
        std::shared_ptr<VulkanGraphicsMemoryBlockCollection> blockCollection =
            std::dynamic_pointer_cast<VulkanGraphicsMemoryBlockCollection>(_blockCollections.getActual().at(index));

        GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion =
            blockCollection->Allocate(memoryRequirements.size, memoryRequirements.alignment, allocationFlags);

        return std::static_pointer_cast<GraphicsBuffer>(std::make_shared<VulkanGraphicsBufferImpl<Metadata>>(
            GetDevice(), bufferKind, std::move(blockRegion), cpuAccessKind, vulkanBuffer));
    }

    std::shared_ptr<GraphicsTexture> VulkanGraphicsMemoryAllocator::CreateTexture(
        GraphicsTextureAddressMode addressMode,
        GraphicsTextureKind textureKind,
        GraphicsResourceAccess cpuAccessKind,
        GraphicsResourceAccess gpuAccessKind,
        uint32_t width,
        uint32_t height,
        uint32_t depth,
        GraphicsMemoryRegionAllocationFlags allocationFlags,
        TexelFormat texelFormat)
    {
        VkDevice vulkanDevice = GetDevice()->GetVulkanDevice();
        VkImageType imageType;

        switch (textureKind)
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
        extent.width = width;
        extent.height = height;
        extent.depth = depth;

        VkImageCreateInfo imageCreateInfo{};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.imageType = imageType;
        imageCreateInfo.format = Utilities::Map(texelFormat);
        imageCreateInfo.extent = extent;
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.usage = Utilities::GetVulkanImageUsageKind(textureKind, gpuAccessKind);

        VkImage vulkanImage = VK_NULL_HANDLE;

        VkResult createImageResult = vkCreateImage(vulkanDevice, &imageCreateInfo, nullptr, &vulkanImage);
        if (createImageResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkImage with the specified parameters.",
                                                             createImageResult);
        }

        VkMemoryRequirements memoryRequirements{};
        vkGetImageMemoryRequirements(vulkanDevice, vulkanImage, &memoryRequirements);

        size_t index = GetBlockCollectionIndex(cpuAccessKind, memoryRequirements.memoryTypeBits);
        std::shared_ptr<VulkanGraphicsMemoryBlockCollection> blockCollection =
            std::dynamic_pointer_cast<VulkanGraphicsMemoryBlockCollection>(_blockCollections.getActual().at(index));

        GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion =
            blockCollection->Allocate(memoryRequirements.size, memoryRequirements.alignment, allocationFlags);

        return std::static_pointer_cast<GraphicsTexture>(std::make_shared<VulkanGraphicsTextureImpl<Metadata>>(
            GetDevice(), addressMode, textureKind, std::move(blockRegion), cpuAccessKind, width, height,
            static_cast<uint16_t>(depth), vulkanImage));
    }

    std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator VulkanGraphicsMemoryAllocator::begin()
    {
        return _blockCollections.getActual().begin();
    }

    std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator VulkanGraphicsMemoryAllocator::end()
    {
        return _blockCollections.getActual().end();
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
