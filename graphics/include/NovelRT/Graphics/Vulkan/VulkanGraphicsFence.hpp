// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSFENCE_H
#define NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSFENCE_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsFence final : public GraphicsFence
    {
    private:
        NovelRT::Utilities::Lazy<VkFence> _vulkanFence;
        Threading::VolatileState _state;

        [[nodiscard]] VkFence CreateVulkanFenceSignaled()
        {
            return CreateVulkanFence(VK_FENCE_CREATE_SIGNALED_BIT);
        }
        [[nodiscard]] VkFence CreateVulkanFenceUnsignaled()
        {
            return CreateVulkanFence(static_cast<VkFenceCreateFlagBits>(0));
        }
        [[nodiscard]] VkFence CreateVulkanFence(VkFenceCreateFlagBits flags);
        void DisposeVulkanFence(VkFence vulkanFence) noexcept;
        [[nodiscard]] bool TryWaitInternal(uint64_t millisecondsTimeout);

    public:
        explicit VulkanGraphicsFence(std::shared_ptr<VulkanGraphicsDevice> device, bool isSignaled) noexcept;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::static_pointer_cast<VulkanGraphicsDevice>(GraphicsFence::GetDevice());
        }

        [[nodiscard]] inline VkFence GetVulkanFence()
        {
            return _vulkanFence.getActual();
        }

        [[nodiscard]] bool GetIsSignalled() final;

        void Reset() final;

        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout) final;
        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout) final;

        ~VulkanGraphicsFence() final;
    };
}

#endif // !NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSFENCE_H
