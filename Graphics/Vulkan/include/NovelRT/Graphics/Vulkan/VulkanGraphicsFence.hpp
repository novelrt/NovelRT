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
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsFence<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

        mutable NovelRT::Utilities::Lazy<VkFence> _vulkanFence;
        mutable Threading::VolatileState _state;

    public:
        GraphicsFence(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, bool isSignaled) noexcept;
        ~GraphicsFence() noexcept override;

        [[nodiscard]] bool GetIsSignalled() const;

        void Reset();

        [[nodiscard]] bool TryWait();
        [[nodiscard]] bool TryWait(uint64_t millisecondsTimeout);
        [[nodiscard]] bool TryWait(std::chrono::duration<uint64_t, std::milli> timeout);

        void Wait();
        void Wait(uint64_t millisecondsTimeout);
        void Wait(std::chrono::duration<uint64_t, std::milli> timeout);

        [[nodiscard]] VkFence GetVulkanFence() const;
    };
}
