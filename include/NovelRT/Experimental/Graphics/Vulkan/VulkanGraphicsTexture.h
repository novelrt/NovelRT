// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSTEXTURE_H
#define NOVELRT_VULKANGRAPHICSTEXTURE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
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
        Utilities::Lazy<VkImageView> _vulkanImageView;
        Utilities::Lazy<VkSampler> _vulkanSampler;

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
                              GraphicsResourceCpuAccessKind cpuAccess,
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
        TMetadata _metadata;

    public:
        VulkanGraphicsTextureImpl(std::shared_ptr<VulkanGraphicsDevice> device,
                                  GraphicsTextureKind kind,
                                  GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                                  GraphicsResourceCpuAccessKind cpuAccess,
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

        [[nodiscard]] bool TryAllocate(size_t size,
                                       size_t alignment,
                                       GraphicsMemoryRegion<GraphicsResource>& outRegion) final
        {
            return _metadata.TryAllocate(size, alignment, outRegion);
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator begin() final
        {
            return _metadata.begin();
        }

        [[nodiscard]] std::list<GraphicsMemoryRegion<GraphicsResource>>::iterator end() final
        {
            return _metadata.end();
        }

        ~VulkanGraphicsTextureImpl() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // !NOVELRT_VULKANGRAPHICSTEXTURE_H