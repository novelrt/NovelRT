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
        VulkanGraphicsDevice* _device;

        mutable NovelRT::Utilities::Lazy<VkFence> _vulkanFence;
        mutable Threading::VolatileState _state;

        [[nodiscard]] VkFence CreateVulkanFenceSignaled()
        {
            return CreateVulkanFence(VK_FENCE_CREATE_SIGNALED_BIT);
        }
        [[nodiscard]] VkFence CreateVulkanFenceUnsignaled()
        {
            // NOLINTNEXTLINE(EnumCastOutOfRange): zero-init is the default
            return CreateVulkanFence(static_cast<VkFenceCreateFlagBits>(0));
        }
        [[nodiscard]] VkFence CreateVulkanFence(VkFenceCreateFlagBits flags) const;
        void DisposeVulkanFence(VkFence vulkanFence) const noexcept;
        [[nodiscard]] bool TryWaitInternal(uint64_t millisecondsTimeout);

    public:
        VulkanGraphicsFence(VulkanGraphicsDevice* device, bool isSignaled) noexcept;
        ~VulkanGraphicsFence();

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] VkFence GetVulkanFence()
        {
            return _vulkanFence.Get();
        }

        [[nodiscard]] bool GetIsSignalled();

        void Reset();

        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout);
        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout);

        void Wait(uint64_t millisecondsTimeout)
        {
            if (!TryWait(millisecondsTimeout))
            {
                throw Exceptions::TimeoutException(millisecondsTimeout);
            }
        }

        void Wait(std::chrono::duration<uint64_t, std::milli> timeout)
        {
            if (!TryWait(timeout))
            {
                throw Exceptions::TimeoutException(timeout.count());
            }
        }

        void Wait()
        {
            Wait(std::numeric_limits<uint64_t>::max());
        }
    };
}
