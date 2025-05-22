// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Utilities/Macros.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsFence = GraphicsFence<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;

    VkFence CreateVulkanFence(std::weak_ptr<VulkanGraphicsDevice> device, bool isSignaled)
    {
        VkFence vulkanFence = VK_NULL_HANDLE;

        VkFenceCreateInfo fenceCreateInfo{};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.pNext = nullptr;
        if (isSignaled)
            fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        auto vkDevice = device.lock()->GetVulkanDevice();
        VkResult result = vkCreateFence(vkDevice, &fenceCreateInfo, nullptr, &vulkanFence);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkFence instance.", result);
        }

        return vulkanFence;
    }

    VulkanGraphicsFence::GraphicsFence(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, bool isSignaled) noexcept
        : _device(std::move(device))
        ,  _vulkanFence([device = std::weak_ptr(device), isSignaled]() { return CreateVulkanFence(device, isSignaled); })
    {
        unused(_state.Transition(Threading::VolatileState::Initialised));
    }

    void DisposeVulkanFence(VkDevice device, VkFence vulkanFence)
    {
        if (device != VK_NULL_HANDLE && vulkanFence != VK_NULL_HANDLE)
        {
            vkDestroyFence(device, vulkanFence, nullptr);
        }
    }

    VulkanGraphicsFence::~GraphicsFence() noexcept
    {
        if (_vulkanFence.HasValue())
        {
            DisposeVulkanFence(_device->GetVulkanDevice(), _vulkanFence.Get());
            _vulkanFence.Reset();
        }
    }

    bool VulkanGraphicsFence::IsSignalled() const
    {
        return vkGetFenceStatus(_device->GetVulkanDevice(), GetVulkanFence()) == VK_SUCCESS;
    }

    void VulkanGraphicsFence::Reset()
    {
        VkFence vulkanFence = GetVulkanFence();

        VkResult result = vkResetFences(_device->GetVulkanDevice(), 1, &vulkanFence);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("VkFence instance failed to reset correctly. Reason: " +
                                                        std::to_string(result));
        }
    }

    bool VulkanGraphicsFence::TryWait()
    {
        return TryWait(std::numeric_limits<uint64_t>::max());
    }

    bool VulkanGraphicsFence::TryWait(uint64_t millisecondsTimeout)
    {
        // vkWaitForFences accepts its timeout in nanoseconds
        auto nanosecondsTimeout = millisecondsTimeout * 1000;
        bool fenceSignalled = IsSignalled();

        if (!fenceSignalled)
        {
            VkFence vulkanFence = GetVulkanFence();
            VkResult result = vkWaitForFences(_device->GetVulkanDevice(), 1, &vulkanFence, VK_TRUE, nanosecondsTimeout);

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

    void VulkanGraphicsFence::Wait()
    {
        return Wait(std::numeric_limits<uint64_t>::max());
    }

    void VulkanGraphicsFence::Wait(uint64_t millisecondsTimeout)
    {
        // vkWaitForFences accepts its timeout in nanoseconds
        auto nanosecondsTimeout = millisecondsTimeout * 1000;
        bool fenceSignalled = IsSignalled();

        if (!fenceSignalled)
        {
            VkFence vulkanFence = GetVulkanFence();
            VkResult result = vkWaitForFences(_device->GetVulkanDevice(), 1, &vulkanFence, VK_TRUE, nanosecondsTimeout);

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
    }

    VkFence VulkanGraphicsFence::GetVulkanFence() const
    {
        return _vulkanFence.Get();
    }
}
