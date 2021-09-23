// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSMEMORYALLOCATOR_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSMEMORYALLOCATOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsMemoryAllocator final
        : public GraphicsMemoryAllocatorImpl<IGraphicsMemoryRegionCollection<GraphicsResource>::DefaultMetadata>
    {
    private:
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>> _blockCollections;
        Threading::VolatileState _state;

        [[nodiscard]] size_t GetBlockCollectionIndex(GraphicsResourceAccess cpuAccess, uint32_t memoryTypeBits);

    public:
        VulkanGraphicsMemoryAllocator(std::shared_ptr<VulkanGraphicsDevice> device,
                                      GraphicsMemoryAllocatorSettings settings);

        [[nodiscard]] inline int32_t GetCount() final
        {
            // TODO: Cursed.
            return static_cast<int32_t>(_blockCollections.getActual().size());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsDeviceObject::GetDevice());
        }

        std::shared_ptr<GraphicsBuffer> CreateBuffer(GraphicsBufferKind bufferKind,
                                                     GraphicsResourceAccess cpuAccessKind,
                                                     GraphicsResourceAccess gpuAccessKind,
                                                     size_t size,
                                                     GraphicsMemoryRegionAllocationFlags allocationFlags) final;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture(
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            GraphicsMemoryRegionAllocationFlags allocationFlags,
            TexelFormat texelFormat) final;

        [[nodiscard]] inline GraphicsMemoryBudget GetBudget(
            std::shared_ptr<VulkanGraphicsMemoryBlockCollection> /*collection*/)
        {
            return GraphicsMemoryBudget(std::numeric_limits<uint64_t>::max(), 0, 0, 0);
        }

        [[nodiscard]] inline GraphicsMemoryBudget GetBudget(
            std::shared_ptr<GraphicsMemoryBlockCollection> blockCollection) final
        {
            return GetBudget(std::dynamic_pointer_cast<VulkanGraphicsMemoryBlockCollection>(blockCollection));
        }

        [[nodiscard]] std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator begin() final;
        [[nodiscard]] std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator end() final;

        // TODO: I don't know if I'm supposed to do anything here based on the TerraFX code.
        ~VulkanGraphicsMemoryAllocator() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSMEMORYALLOCATOR_H
