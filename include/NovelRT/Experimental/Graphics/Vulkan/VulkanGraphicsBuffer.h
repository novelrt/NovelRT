// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsBuffer final : public GraphicsBuffer
    {
    private:
        VkBuffer _vulkanBuffer;
        Threading::VolatileState _state;

    protected:
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
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSBUFFER_H
