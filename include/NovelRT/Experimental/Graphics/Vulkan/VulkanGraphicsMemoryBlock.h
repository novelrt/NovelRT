// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSMEMORYBLOCK_H
#define NOVELRT_VULKANGRAPHICSMEMORYBLOCK_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsMemoryBlock : public GraphicsMemoryBlock
    {
    private:
        Utilities::Lazy<VkDeviceMemory> _vulkanDeviceMemory;

        VkDeviceMemory CreateVulkanDeviceMemory();
        void DisposeVulkanDeviceMemory() noexcept;

    protected:
        Threading::VolatileState _state;

        VulkanGraphicsDevice* GetDeviceInternal() const noexcept final;

    public:
        VulkanGraphicsMemoryBlock(std::shared_ptr<VulkanGraphicsDevice> device,
                                  std::shared_ptr<VulkanGraphicsMemoryBlockCollection> collection);

        ~VulkanGraphicsMemoryBlock() override;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryBlockCollection> GetCollection() const noexcept
        {
            return std::static_pointer_cast<VulkanGraphicsMemoryBlockCollection>(GraphicsMemoryBlock::GetCollection());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GetDeviceInternal()->shared_from_this());
        }

        [[nodiscard]] inline VkDeviceMemory GetVulkanDeviceMemory()
        {
            return _vulkanDeviceMemory.getActual();
        }
    };

    template<typename TMetadata> class VulkanGraphicsMemoryBlockImpl final : public VulkanGraphicsMemoryBlock
    {
    private:
        TMetadata _metadata;

    public:
        VulkanGraphicsMemoryBlockImpl(std::shared_ptr<VulkanGraphicsDevice> device,
                                      std::shared_ptr<VulkanGraphicsMemoryBlockCollection> collection,
                                      size_t size)
            : VulkanGraphicsMemoryBlock(std::move(device), std::move(collection)), _metadata()
        {
            static_assert(
                std::is_base_of_v<IGraphicsMemoryRegionCollection<GraphicsMemoryBlock>::IMetadata, TMetadata>);

            const GraphicsMemoryAllocatorSettings& allocatorSettings = GetCollection()->GetAllocator()->GetSettings();

            size_t minimumAllocatedRegionSize = allocatorSettings.MinimumAllocatedRegionMarginSize.value_or(0);
            size_t minimumFreeRegionSizeToRegister = allocatorSettings.MinimumFreeRegionSizeToRegister;

            _metadata.Initialise(std::static_pointer_cast<VulkanGraphicsMemoryBlockImpl>(shared_from_this()), GetSize(),
                                 minimumAllocatedRegionSize, minimumFreeRegionSizeToRegister);

            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] int32_t GetAllocatedRegionCount() const noexcept final
        {
            return _metadata.GetAllocatedRegionCount();
        }

        [[nodiscard]] int32_t GetCount() const noexcept final
        {
            return _metadata.GetCount();
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

        GraphicsMemoryRegion<GraphicsMemoryBlock> Allocate(size_t size, size_t alignment) final
        {
            return _metadata.Allocate(size, alignment);
        }

        void Clear() final
        {
            _metadata.Clear();
        }

        void Free(const GraphicsMemoryRegion<GraphicsMemoryBlock>& region) final
        {
            _metadata.Free(region);
        }

        [[nodiscard]] bool TryAllocate(size_t size,
                                       size_t alignment,
                                       GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion) final
        {
            return _metadata.TryAllocate(size, alignment, outRegion);
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsMemoryBlock>>::iterator begin() final
        {
            return _metadata.begin();
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsMemoryBlock>>::iterator end() final
        {
            return _metadata.end();
        }

        ~VulkanGraphicsMemoryBlockImpl() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSMEMORYBLOCK_H
