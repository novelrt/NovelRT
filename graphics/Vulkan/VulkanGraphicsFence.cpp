// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>

namespace NovelRT::Graphics::Vulkan
{

    VkFence VulkanGraphicsFence::CreateVulkanFence(VkFenceCreateFlagBits flags)
    {
        VkFence vulkanFence = VK_NULL_HANDLE;

        VkFenceCreateInfo fenceCreateInfo{};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.pNext = nullptr;
        fenceCreateInfo.flags = flags;

        VkResult result = vkCreateFence(GetDevice()->GetVulkanDevice(), &fenceCreateInfo, nullptr, &vulkanFence);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkFence instance.", result);
        }

        return vulkanFence;
    }

    void VulkanGraphicsFence::DisposeVulkanFence(VkFence vulkanFence) noexcept
    {
        if (vulkanFence != VK_NULL_HANDLE)
        {
            vkDestroyFence(GetDevice()->GetVulkanDevice(), vulkanFence, nullptr);
        }
    }

    bool VulkanGraphicsFence::TryWaitInternal(uint64_t millisecondsTimeout)
    {
        bool fenceSignalled = GetIsSignalled();

        if (!fenceSignalled)
        {
            VkFence vulkanFence = GetVulkanFence();
            VkResult result =
                vkWaitForFences(GetDevice()->GetVulkanDevice(), 1, &vulkanFence, VK_TRUE, millisecondsTimeout);

            if (result == VK_SUCCESS)
            {
                fenceSignalled = true;
            }
            else if (result != VK_TIMEOUT)
            {
                throw Exceptions::InvalidOperationException(
                    "VkFence instance failed to either succeed or time out correctly. Reason: " +
                    std::to_string(result));
            }
        }

        return fenceSignalled;
    }

    VulkanGraphicsFence::VulkanGraphicsFence(std::shared_ptr<VulkanGraphicsDevice> device, bool isSignaled) noexcept
        : GraphicsFence(device),
          _vulkanFence([=]() { return isSignaled ? CreateVulkanFenceSignaled() : CreateVulkanFenceUnsignaled(); }),
          _state()
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    bool VulkanGraphicsFence::GetIsSignalled()
    {
        return vkGetFenceStatus(GetDevice()->GetVulkanDevice(), GetVulkanFence()) == VK_SUCCESS;
    }

    void VulkanGraphicsFence::Reset()
    {
        VkFence vulkanFence = GetVulkanFence();

        VkResult result = vkResetFences(GetDevice()->GetVulkanDevice(), 1, &vulkanFence);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("VkFence instance failed to reset correctly. Reason: " +
                                                        std::to_string(result));
        }
    }

    bool VulkanGraphicsFence::TryWait(uint64_t millisecondsTimeout)
    {
        return TryWaitInternal(millisecondsTimeout);
    }

    bool VulkanGraphicsFence::TryWait(std::chrono::duration<uint64_t, std::milli> timeout)
    {
        uint64_t millisecondsTimeout = timeout.count();
        return TryWaitInternal(millisecondsTimeout);
    }

    VulkanGraphicsFence::~VulkanGraphicsFence()
    {
        if (_vulkanFence.isCreated())
        {
            DisposeVulkanFence(_vulkanFence.getActual());
            _vulkanFence.reset();
        }
    }
} // namespace NovelRT::Graphics::Vulkan
