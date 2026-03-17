// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp>
#include <NovelRT/Utilities/Macros.hpp>

#include <limits>

namespace NovelRT::Graphics
{
    using VulkanGraphicsSemaphore = GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;

    static VkSemaphore CreateVulkanSemaphore(VulkanGraphicsDevice* device, uint64_t initialValue)
    {
        VkSemaphore vulkanSemaphore = VK_NULL_HANDLE;

        VkSemaphoreTypeCreateInfo typeCreateInfo{};
        typeCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
        typeCreateInfo.pNext = nullptr;
        typeCreateInfo.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;
        typeCreateInfo.initialValue = initialValue;

        VkSemaphoreCreateInfo semaphoreCreateInfo{};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        if (initialValue != std::numeric_limits<uint64_t>::max())
        {
            semaphoreCreateInfo.pNext = &typeCreateInfo;
        }

        auto vkDevice = device->GetVulkanDevice();
        VkResult result = vkCreateSemaphore(vkDevice, &semaphoreCreateInfo, nullptr, &vulkanSemaphore);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkSemaphore instance.", result);
        }

        return vulkanSemaphore;
    }

    VulkanGraphicsSemaphore::GraphicsSemaphore(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                                               uint64_t initialValue) noexcept
        : _device(std::move(device)), _semaphore(CreateVulkanSemaphore(_device.get(), initialValue))
    {
    }

    void DisposeVulkanSemaphore(VkDevice device, VkSemaphore vulkanSemaphore)
    {
        if (device != VK_NULL_HANDLE && vulkanSemaphore != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(device, vulkanSemaphore, nullptr);
        }
    }

    VulkanGraphicsSemaphore::~GraphicsSemaphore() noexcept
    {
        vkDestroySemaphore(_device->GetVulkanDevice(), _semaphore, nullptr);
    }

    uint64_t VulkanGraphicsSemaphore::GetValue() const
    {
        uint64_t value;
        VkResult result = vkGetSemaphoreCounterValue(_device->GetVulkanDevice(), _semaphore, &value);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("Failed to get VkSemaphore value: " + std::to_string(result));
        }

        return value;
    }

    void VulkanGraphicsSemaphore::Signal(uint64_t value)
    {
        VkSemaphoreSignalInfo signalInfo{};
        signalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
        signalInfo.pNext = nullptr;
        signalInfo.semaphore = _semaphore;
        signalInfo.value = value;

        VkResult result = vkSignalSemaphore(_device->GetVulkanDevice(), &signalInfo);
        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("Failed to signal VkSemaphore: " + std::to_string(result));
        }
    }

    bool VulkanGraphicsSemaphore::Wait(uint64_t value)
    {
        return Wait(value, std::numeric_limits<uint64_t>::max());
    }

    bool VulkanGraphicsSemaphore::Wait(uint64_t value, uint64_t millisecondsTimeout)
    {
        // vkWaitSemaphores accepts its timeout in nanoseconds
        auto nanosecondsTimeout = millisecondsTimeout * 1000;

        VkSemaphoreWaitInfo waitInfo{};
        waitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
        waitInfo.pNext = nullptr;
        waitInfo.semaphoreCount = 1;
        waitInfo.pSemaphores = &_semaphore;
        waitInfo.pValues = &value;

        VkResult result = vkWaitSemaphores(_device->GetVulkanDevice(), &waitInfo, nanosecondsTimeout);

        if (result != VK_SUCCESS && result != VK_TIMEOUT)
        {
            throw Exceptions::InvalidOperationException("Failed to wait on VkSemaphore: " + std::to_string(result));
        }

        return result == VK_SUCCESS;
    }

    VkSemaphore VulkanGraphicsSemaphore::GetVulkanSemaphore() const
    {
        return _semaphore;
    }
}
