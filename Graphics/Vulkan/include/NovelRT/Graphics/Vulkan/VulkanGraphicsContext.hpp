#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <memory>
#include <map>
#include <vector>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsContext<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        size_t _index;

        std::map<
            std::weak_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>>,
            std::vector<std::weak_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>>>,
            std::owner_less<>> _vulkanDescriptorSets;
        std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> _fence;
        std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> _waitForExecuteCompletionFence;

        mutable NovelRT::Utilities::Lazy<VkCommandBuffer> _vulkanCommandBuffer;
        mutable NovelRT::Utilities::Lazy<VkCommandPool> _vulkanCommandPool;
        mutable NovelRT::Utilities::Lazy<VkFramebuffer> _vulkanFramebuffer;
        mutable NovelRT::Utilities::Lazy<VkImageView> _vulkanSwapChainImageView;

        Threading::VolatileState _state;

        void DestroyDescriptorSets();

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsContext<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsContext(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, size_t index) noexcept;
        ~GraphicsContext() final;

        [[nodiscard]] std::weak_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> GetFence() const noexcept;

        [[nodiscard]] size_t GetIndex() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> BeginFrame();
        void EndFrame() const;

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] VkCommandBuffer GetVulkanCommandBuffer() const;
        [[nodiscard]] VkCommandPool GetVulkanCommandPool() const;
        [[nodiscard]] VkFramebuffer GetVulkanFramebuffer() const;
        [[nodiscard]] VkImageView GetVulkanSwapChainImageView() const;

        [[nodiscard]] std::weak_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> GetWaitForExecuteCompletionFence() const noexcept;

        void RegisterDescriptorSetForFrame(std::weak_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> signature, std::weak_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>> set);
    };
}
