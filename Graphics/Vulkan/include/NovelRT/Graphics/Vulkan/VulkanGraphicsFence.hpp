#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/TimeoutException.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <chrono>
#include <cstdint>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

    class VulkanGraphicsFence
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
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
        VulkanGraphicsFence(std::shared_ptr<VulkanGraphicsDevice> device, bool isSignaled) noexcept;
        ~VulkanGraphicsFence();

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] inline VkFence GetVulkanFence()
        {
            return _vulkanFence.getActual();
        }

        [[nodiscard]] bool GetIsSignalled();

        void Reset();

        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout);
        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout);

        inline void Wait(uint64_t millisecondsTimeout)
        {
            if (!TryWait(millisecondsTimeout))
            {
                throw Exceptions::TimeoutException(millisecondsTimeout);
            }
        }

        inline void Wait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            if (!TryWait(timeout))
            {
                throw Exceptions::TimeoutException(timeout.count());
            }
        }

        inline void Wait()
        {
            Wait(std::numeric_limits<uint64_t>::max());
        }
    };
}
