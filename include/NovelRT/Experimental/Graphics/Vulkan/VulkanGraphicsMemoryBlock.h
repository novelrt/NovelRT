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
        NovelRT::Utilities::Lazy<VkDeviceMemory> _vulkanDeviceMemory;

        VkDeviceMemory CreateVulkanDeviceMemory();
        void DisposeVulkanDeviceMemory() noexcept;

    protected:
        Threading::VolatileState _state;

        VulkanGraphicsDevice* GetDeviceInternal() const noexcept final;

    public:
        VulkanGraphicsMemoryBlock(const std::shared_ptr<VulkanGraphicsDevice>& device,
                                  const std::shared_ptr<VulkanGraphicsMemoryBlockCollection>& collection);

        ~VulkanGraphicsMemoryBlock() override;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryBlockCollection> GetCollection()
        {
            return std::static_pointer_cast<VulkanGraphicsMemoryBlockCollection>(GraphicsMemoryBlock::GetCollection());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice()
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
        NovelRT::Utilities::Lazy<TMetadata> _metadata;

    public:
        VulkanGraphicsMemoryBlockImpl(std::shared_ptr<VulkanGraphicsDevice> device,
                                      std::shared_ptr<VulkanGraphicsMemoryBlockCollection> collection,
                                      size_t size)
            : VulkanGraphicsMemoryBlock(std::move(device), std::move(collection)),
              _metadata(
                  [&]()
                  {
                      TMetadata metadata(GetDevice());
                      const GraphicsMemoryAllocatorSettings& allocatorSettings =
                          GetCollection()->GetAllocator()->GetSettings();

                      size_t minimumAllocatedRegionSize =
                          allocatorSettings.MinimumAllocatedRegionMarginSize.value_or(0);
                      size_t minimumFreeRegionSizeToRegister = allocatorSettings.MinimumFreeRegionSizeToRegister;
                      metadata.Initialise(
                          std::static_pointer_cast<VulkanGraphicsMemoryBlockImpl>(shared_from_this()), size,
                          minimumAllocatedRegionSize, minimumFreeRegionSizeToRegister);
                      return metadata;
                  })
        {
            static_assert(
                std::is_base_of_v<IGraphicsMemoryRegionCollection<GraphicsMemoryBlock>::IMetadata, TMetadata>);

            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] int32_t GetAllocatedRegionCount() final
        {
            return _metadata.getActual().GetAllocatedRegionCount();
        }

        [[nodiscard]] int32_t GetCount()
        {
            return _metadata.getActual().GetCount();
        }

        [[nodiscard]] bool GetIsEmpty() final
        {
            return _metadata.getActual().GetIsEmpty();
        }

        [[nodiscard]] size_t GetLargestFreeRegionSize() final
        {
            return _metadata.getActual().GetLargestFreeRegionSize();
        }

        [[nodiscard]] size_t GetMinimumAllocatedRegionMarginSize() final
        {
            return _metadata.getActual().GetMinimumAllocatedRegionMarginSize();
        }

        [[nodiscard]] size_t GetMinimumFreeRegionSizeToRegister() final
        {
            return _metadata.getActual().GetMinimumFreeRegionSizeToRegister();
        }

        [[nodiscard]] size_t GetSize() final
        {
            return _metadata.getActual().GetSize();
        }

        [[nodiscard]] size_t GetTotalFreeRegionSize() final
        {
            return _metadata.getActual().GetTotalFreeRegionSize();
        }

        GraphicsMemoryRegion<GraphicsMemoryBlock> Allocate(size_t size, size_t alignment) final
        {
            return _metadata.getActual().Allocate(size, alignment);
        }

        void Clear() final
        {
            _metadata.getActual().Clear();
        }

        void Free(const GraphicsMemoryRegion<GraphicsMemoryBlock>& region) final
        {
            _metadata.getActual().Free(region);
        }

        [[nodiscard]] bool TryAllocate(size_t size,
                                       size_t alignment,
                                       GraphicsMemoryRegion<GraphicsMemoryBlock>& outRegion) final
        {
            return _metadata.getActual().TryAllocate(size, alignment, outRegion);
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsMemoryBlock>>::iterator begin() final
        {
            return _metadata.getActual().begin();
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsMemoryBlock>>::iterator end() final
        {
            return _metadata.getActual().end();
        }

        ~VulkanGraphicsMemoryBlockImpl() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSMEMORYBLOCK_H
