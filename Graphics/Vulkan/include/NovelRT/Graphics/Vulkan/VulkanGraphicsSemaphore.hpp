#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/GraphicsSemaphore.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <chrono>
#include <cstdint>

#include <vulkan/vulkan.h>

#include <chrono>
#include <cstdint>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsSemaphore<Vulkan::VulkanGraphicsBackend> : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

        VkSemaphore _semaphore;

    public:
        GraphicsSemaphore(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, uint64_t initialValue) noexcept;
        ~GraphicsSemaphore() noexcept;

        [[nodiscard]] uint64_t GetValue() const;

        void Signal(uint64_t value);

        bool Wait(uint64_t value);
        bool Wait(uint64_t value, uint64_t millisecondsTimeout);
        bool Wait(uint64_t value, std::chrono::duration<uint64_t, std::milli> timeout);

        template<typename Rep, typename Period>
        bool Wait(std::chrono::duration<Rep, Period> timeout)
        {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);

            if (ms.count() < 0)
            {
                throw Exceptions::InvalidOperationException("Timeout must be positive");
            }

            return Wait(ms.count());
        }

        [[nodiscard]] VkSemaphore GetVulkanSemaphore() const;
    };
}
