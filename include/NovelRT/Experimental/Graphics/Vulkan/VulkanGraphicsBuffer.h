// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsBuffer : public GraphicsBuffer
    {
    private:
        VkBuffer _vulkanBuffer;

    protected:
        Threading::VolatileState _state;
        [[nodiscard]] VulkanGraphicsDevice* GetDeviceInternal() const noexcept final;

    public:
        VulkanGraphicsBuffer(std::shared_ptr<VulkanGraphicsDevice> device,
                             GraphicsBufferKind kind,
                             GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                             GraphicsResourceCpuAccessKind cpuAccess,
                             VkBuffer buffer);

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsMemoryAllocator>(GraphicsBuffer::GetAllocator());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryBlock> GetBlock() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsMemoryBlock>(GraphicsBuffer::GetBlock());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GetDeviceInternal()->shared_from_this());
        }

        [[nodiscard]] inline VkBuffer GetVulkanBuffer() const noexcept
        {
            return _vulkanBuffer;
        }

        [[nodiscard]] void* MapUntyped() final;
        [[nodiscard]] void* MapUntyped(size_t rangeOffset, size_t rangeLength) final;
        [[nodiscard]] const void* MapForReadUntyped() final;
        [[nodiscard]] const void* MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength) final;
        void Unmap() final;
        void UnmapAndWrite() final;
        void UnmapAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;
        ~VulkanGraphicsBuffer() override;
    };

    template<typename TMetadata> class VulkanGraphicsBufferImpl final : public VulkanGraphicsBuffer
    {
    private:
        TMetadata _metadata;

    public:
        VulkanGraphicsBufferImpl(std::shared_ptr<VulkanGraphicsDevice> device,
                                 GraphicsBufferKind kind,
                                 GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                                 GraphicsResourceCpuAccessKind cpuAccess,
                                 VkBuffer vulkanBuffer)
            : VulkanGraphicsBuffer(std::move(device), kind, std::move(blockRegion), cpuAccess, vulkanBuffer),
              _metadata()
        {
            static_assert(std::is_base_of_v<IGraphicsMemoryRegionCollection<GraphicsResource>::IMetadata, TMetadata>);

            std::shared_ptr<GraphicsMemoryBlock> block = GetBlockRegion().GetCollection();

            size_t minimumAllocatedRegionMarginSize = block->GetMinimumAllocatedRegionMarginSize();
            size_t minimumFreeRegionSizeToRegister = block->GetMinimumFreeRegionSizeToRegister();

            _metadata.Initialise(std::static_pointer_cast<VulkanGraphicsBufferImpl>(shared_from_this()),
                                 blockRegion.GetSize(), minimumAllocatedRegionMarginSize,
                                 minimumFreeRegionSizeToRegister);

            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] int32_t GetAllocatedRegionCount() const noexcept final
        {
            return _metadata.GetAllocatedRegionCount();
        }

        [[nodiscard]] int32_t GetCount() const noexcept final
        {
            return static_cast<int32_t>(_metadata.GetCount());
        }

        [[nodiscard]] bool GetIsEmpty() const noexcept final
        {
            return _metadata.GetIsEmpty();
        }

        [[nodiscard]] size_t GetLargestFreeRegionSize() const noexcept final
        {
            return _metadata.GetLargestFreeRegionSize();
        }

        [[nodiscard]] size_t GetMinimumAllocatedRegionMarginSize() const noexcept final
        {
            return _metadata.GetMinimumAllocatedRegionMarginSize();
        }

        [[nodiscard]] size_t GetMinimumFreeRegionSizeToRegister() const noexcept final
        {
            return _metadata.GetMinimumFreeRegionSizeToRegister();
        }

        [[nodiscard]] size_t GetTotalFreeRegionSize() const noexcept final
        {
            return _metadata.GetTotalFreeRegionSize();
        }

        GraphicsMemoryRegion<GraphicsResource> Allocate(size_t size, size_t alignment) final
        {
            return _metadata.Allocate(size, alignment);
        }

        void Clear() final
        {
            _metadata.Clear();
        }

        void Free(const GraphicsMemoryRegion<GraphicsResource>& region) final
        {
            _metadata.Free(region);
        }

        bool TryAllocate(size_t size, size_t alignment, GraphicsMemoryRegion<GraphicsResource>& outRegion) final
        {
            return _metadata.TryAllocate(size, alignment, outRegion);
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator begin() final
        {
            return _metadata.begin();
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator end() override
        {
            return _metadata.end();
        }

        ~VulkanGraphicsBufferImpl() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H