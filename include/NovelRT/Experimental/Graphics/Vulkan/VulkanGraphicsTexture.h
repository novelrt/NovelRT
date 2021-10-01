// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSTEXTURE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSTEXTURE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsTexture : public GraphicsTexture
    {
    private:
        // TODO: These don't seem to be used anywhere? why? What is the point of these?
        static inline const int32_t Binding = 2;
        static inline const int32_t Bound = 3;

        VkImage _vulkanImage;

        NovelRT::Utilities::Lazy<VkImageView> _vulkanImageView;
        NovelRT::Utilities::Lazy<VkSampler> _vulkanSampler;

        [[nodiscard]] VkImageView CreateVulkanImageView();
        [[nodiscard]] VkSampler CreateVulkanSampler();
        void DisposeVulkanImage() noexcept;
        void DisposeVulkanImageView() noexcept;
        void DisposeVulkanSampler() noexcept;

    protected:
        Threading::VolatileState _state;
        [[nodiscard]] VulkanGraphicsDevice* GetDeviceInternal() const noexcept final;

    public:
        VulkanGraphicsTexture(std::shared_ptr<VulkanGraphicsDevice> device,
                              GraphicsTextureKind kind,
                              GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                              GraphicsResourceAccess cpuAccess,
                              uint32_t width,
                              uint32_t height,
                              uint16_t depth,
                              VkImage vulkanImage);

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsMemoryAllocator>(GraphicsTexture::GetAllocator());
        }

        [[nodiscard]] inline VkImage GetVulkanImage() const noexcept
        {
            return _vulkanImage;
        }

        [[nodiscard]] inline VkImageView GetVulkanImageView()
        {
            return _vulkanImageView.getActual();
        }

        [[nodiscard]] inline VkSampler GetVulkanSampler()
        {
            return _vulkanSampler.getActual();
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryBlock> GetBlock() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsMemoryBlock>(GraphicsTexture::GetBlock());
        }

        [[nodiscard]] void* MapUntyped() final;
        [[nodiscard]] void* MapUntyped(size_t rangeOffset, size_t rangeLength) final;
        [[nodiscard]] const void* MapForReadUntyped() final;
        [[nodiscard]] const void* MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength) final;
        void Unmap() final;
        void UnmapAndWrite() final;
        void UnmapAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        ~VulkanGraphicsTexture() override;
    };

    template<typename TMetadata> class VulkanGraphicsTextureImpl final : public VulkanGraphicsTexture
    {
    private:
        NovelRT::Utilities::Lazy<TMetadata> _metadata;

    public:
        VulkanGraphicsTextureImpl(std::shared_ptr<VulkanGraphicsDevice> device,
                                  GraphicsTextureKind kind,
                                  GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                                  GraphicsResourceAccess cpuAccess,
                                  uint32_t width,
                                  uint32_t height,
                                  uint16_t depth,
                                  VkImage vulkanImage)
            : VulkanGraphicsTexture(std::move(device),
                                    kind,
                                    std::move(blockRegion),
                                    cpuAccess,
                                    width,
                                    height,
                                    depth,
                                    vulkanImage),
              _metadata([&]() {
                  TMetadata metadata(GraphicsDeviceObject::GetDevice());
                  std::shared_ptr<GraphicsMemoryBlock> block = GetBlockRegion().GetCollection();

                  size_t minimumAllocatedRegionMarginSize = block->GetMinimumAllocatedRegionMarginSize();
                  size_t minimumFreeRegionSizeToRegister = block->GetMinimumFreeRegionSizeToRegister();

                  metadata.Initialise(std::static_pointer_cast<VulkanGraphicsBufferImpl<TMetadata>>(shared_from_this()),
                                      blockRegion.GetSize(), minimumAllocatedRegionMarginSize,
                                      minimumFreeRegionSizeToRegister);

                  return metadata;
              })
        {
            static_assert(std::is_base_of_v<IGraphicsMemoryRegionCollection<GraphicsResource>::IMetadata, TMetadata>);

            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] int32_t GetAllocatedRegionCount() final
        {
            return _metadata.getActual().GetAllocatedRegionCount();
        }

        [[nodiscard]] size_t GetCount() final
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

        [[nodiscard]] size_t GetTotalFreeRegionSize() final
        {
            return _metadata.getActual().GetTotalFreeRegionSize();
        }

        GraphicsMemoryRegion<GraphicsResource> Allocate(size_t size, size_t alignment) final
        {
            return _metadata.getActual().Allocate(size, alignment);
        }

        void Clear() final
        {
            _metadata.getActual().Clear();
        }

        void Free(const GraphicsMemoryRegion<GraphicsResource>& region) final
        {
            _metadata.getActual().Free(region);
        }

        [[nodiscard]] bool TryAllocate(size_t size,
                                       size_t alignment,
                                       GraphicsMemoryRegion<GraphicsResource>& outRegion) final
        {
            return _metadata.getActual().TryAllocate(size, alignment, outRegion);
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator begin() final
        {
            return _metadata.getActual().begin();
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator end() final
        {
            return _metadata.getActual().end();
        }

        ~VulkanGraphicsTextureImpl() final = default;
    };
} 

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSTEXTURE_H
