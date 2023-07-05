#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Utilities/Lazy.h>
#include <NovelRT/Threading/Threading.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

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
