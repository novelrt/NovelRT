#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{

    template<>
    class GraphicsContext<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

        mutable NovelRT::Utilities::Lazy<VkCommandPool> _vulkanCommandPool;

        Threading::VolatileState _state;

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsContext<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsContext(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device) noexcept;
        ~GraphicsContext() final;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;

        void BeginFrame();
        [[nodiscard]] std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> CreateCmdList(
            std::optional<SecondaryCmdListInfo<Vulkan::VulkanGraphicsBackend>> secondaryContextData = {});
        void EndFrame();

        [[nodiscard]] VkCommandPool GetVulkanCommandPool() const;
    };
}
