#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Threading/Threading.h>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipelineSignature;
    class VulkanGraphicsDevice;
    class VulkanGraphicsCmdList;
    class VulkanGraphicsDescriptorSet;

    class VulkanGraphicsContext : public std::enable_shared_from_this<VulkanGraphicsContext>
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
        size_t _index;

            std::unordered_map<std::shared_ptr<VulkanGraphicsPipelineSignature>, std::vector<std::shared_ptr<VulkanGraphicsDescriptorSet>>>
            _vulkanDescriptorSets;
        std::shared_ptr<VulkanGraphicsFence> _fence;
        std::shared_ptr<VulkanGraphicsFence> _waitForExecuteCompletionFence;

        NovelRT::Utilities::Lazy<VkCommandBuffer> _vulkanCommandBuffer;
        NovelRT::Utilities::Lazy<VkCommandPool> _vulkanCommandPool;
        NovelRT::Utilities::Lazy<VkFramebuffer> _vulkanFramebuffer;
        NovelRT::Utilities::Lazy<VkImageView> _vulkanSwapChainImageView;

        Threading::VolatileState _state;

        VkCommandBuffer CreateVulkanCommandBuffer();
        VkCommandPool CreateVulkanCommandPool();
        VkFramebuffer CreateVulkanFramebuffer();
        VkImageView CreateVulkanSwapChainImageView();
        void DisposeVulkanCommandBuffer(VkCommandBuffer vulkanCommandBuffer) noexcept;
        void DisposeVulkanCommandPool(VkCommandPool vulkanCommandPool) noexcept;
        void DisposeVulkanFramebuffer(VkFramebuffer vulkanFramebuffer) noexcept;
        void DisposeVulkanSwapChainImageView(VkImageView vulkanSwapChainImageView) noexcept;
        //void BeginCopy(VkImage vulkanImage) noexcept;
        //void EndCopy(VkImage vulkanImage) noexcept;
        void DestroyDescriptorSets();

    public:
        VulkanGraphicsContext(std::shared_ptr<VulkanGraphicsDevice> device, size_t index) noexcept;

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] inline size_t GetIndex() const noexcept
        {
            return _index;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsFence> GetFence() const noexcept
        {
            return _fence;
        }

        [[nodiscard]] inline VkCommandBuffer GetVulkanCommandBuffer()
        {
            return _vulkanCommandBuffer.getActual();
        }

        [[nodiscard]] inline VkCommandPool GetVulkanCommandPool()
        {
            return _vulkanCommandPool.getActual();
        }

        [[nodiscard]] inline VkFramebuffer GetVulkanFramebuffer()
        {
            return _vulkanFramebuffer.getActual();
        }

        [[nodiscard]] inline VkImageView GetVulkanSwapChainImageView()
        {
            return _vulkanSwapChainImageView.getActual();
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsFence> GetWaitForExecuteCompletionFence() const noexcept
        {
            return _waitForExecuteCompletionFence;
        }

        [[nodiscard]] std::shared_ptr<VulkanGraphicsCmdList> BeginFrame();

        void RegisterDescriptorSetForFrame(std::shared_ptr<VulkanGraphicsPipelineSignature> signature, std::shared_ptr<VulkanGraphicsDescriptorSet> set);

        void EndDrawing();

        void EndFrame();

        void ResetContext();

        ~VulkanGraphicsContext();
    };
}
