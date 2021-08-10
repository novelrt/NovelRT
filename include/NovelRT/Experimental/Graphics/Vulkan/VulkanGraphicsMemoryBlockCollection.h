// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSMEMORYBLOCKCOLLECTION_H
#define NOVELRT_VULKANGRAPHICSMEMORYBLOCKCOLLECTION_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsMemoryBlockCollection final : public GraphicsMemoryBlockCollection
    {
    private:
        uint32_t _vulkanMemoryTypeIndex;

    protected:
        VulkanGraphicsMemoryBlock* CreateBlock(size_t size) final;

    public:
        VulkanGraphicsMemoryBlockCollection(std::shared_ptr<VulkanGraphicsDevice> device,
                                            std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                                            uint32_t memoryTypeIndex);

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsMemoryAllocator>(
                GraphicsMemoryBlockCollection::GetAllocator());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsMemoryBlockCollection::GetDevice());
        }

        [[nodiscard]] inline uint32_t GetVulkanMemoryTypeIndex() const noexcept
        {
            return _vulkanMemoryTypeIndex;
        }

        ~VulkanGraphicsMemoryBlockCollection() final = default;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSMEMORYBLOCKCOLLECTION_H