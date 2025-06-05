#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <chrono>
#include <cstdint>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsFence<Vulkan::VulkanGraphicsBackend> : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

        mutable NovelRT::Utilities::Lazy<VkFence> _vulkanFence;
        mutable Threading::VolatileState _state;

    public:
        GraphicsFence(std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, bool isSignaled) noexcept;
        ~GraphicsFence() noexcept override;

        [[nodiscard]] bool IsSignalled() const;

        void Reset();

        [[nodiscard]] bool TryWait();
        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout);

        template<typename Rep, typename Period>
        [[nodiscard]] bool TryWait(std::chrono::duration<Rep, Period> timeout)
        {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);

            if (ms.count() < 0)
            {
                throw Exceptions::InvalidOperationException("Timeout must be positive");
            }

            return TryWait(ms.count());
        }

        void Wait();
        void Wait(uint64_t millisecondsTimeout);

        template<typename Rep, typename Period>
        void Wait(std::chrono::duration<Rep, Period> timeout)
        {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);

            if (ms.count() < 0)
            {
                throw Exceptions::InvalidOperationException("Timeout must be positive");
            }

            Wait(ms.count());
        }

        [[nodiscard]] VkFence GetVulkanFence() const;
    };
}
