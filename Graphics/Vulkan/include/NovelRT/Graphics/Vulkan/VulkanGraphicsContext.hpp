#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <memory>
#include <unordered_map>
#include <vector>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipelineSignature;
    class VulkanGraphicsDevice;
    class VulkanGraphicsCmdList;
    class VulkanGraphicsDescriptorSet;

    class VulkanGraphicsContext
    {
    private:
        VulkanGraphicsDevice* _device;
        size_t _index;

        std::unordered_map<VulkanGraphicsPipelineSignature*, std::vector<VulkanGraphicsDescriptorSet*>> _vulkanDescriptorSets;
        VulkanGraphicsFence* _fence;
        VulkanGraphicsFence* _waitForExecuteCompletionFence;

        mutable NovelRT::Utilities::Lazy<VkCommandBuffer> _vulkanCommandBuffer;
        mutable NovelRT::Utilities::Lazy<VkCommandPool> _vulkanCommandPool;
        mutable NovelRT::Utilities::Lazy<VkFramebuffer> _vulkanFramebuffer;
        mutable NovelRT::Utilities::Lazy<VkImageView> _vulkanSwapChainImageView;

        Threading::VolatileState _state;

        VkCommandBuffer CreateVulkanCommandBuffer() const;
        VkCommandPool CreateVulkanCommandPool() const;
        VkFramebuffer CreateVulkanFramebuffer() const;
        VkImageView CreateVulkanSwapChainImageView() const;
        void DisposeVulkanCommandBuffer(VkCommandBuffer vulkanCommandBuffer) const noexcept;
        void DisposeVulkanCommandPool(VkCommandPool vulkanCommandPool) const noexcept;
        void DisposeVulkanFramebuffer(VkFramebuffer vulkanFramebuffer) const noexcept;
        void DisposeVulkanSwapChainImageView(VkImageView vulkanSwapChainImageView) const noexcept;
        //void BeginCopy(VkImage vulkanImage) noexcept;
        //void EndCopy(VkImage vulkanImage) noexcept;
        void DestroyDescriptorSets();

    public:
        VulkanGraphicsContext(VulkanGraphicsDevice* device, size_t index) noexcept;

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] size_t GetIndex() const noexcept
        {
            return _index;
        }

        [[nodiscard]] VulkanGraphicsFence* GetFence() const noexcept
        {
            return _fence;
        }

        [[nodiscard]] VkCommandBuffer GetVulkanCommandBuffer() const
        {
            return _vulkanCommandBuffer.Get();
        }

        [[nodiscard]] VkCommandPool GetVulkanCommandPool() const
        {
            return _vulkanCommandPool.Get();
        }

        [[nodiscard]] VkFramebuffer GetVulkanFramebuffer() const
        {
            return _vulkanFramebuffer.Get();
        }

        [[nodiscard]] VkImageView GetVulkanSwapChainImageView() const
        {
            return _vulkanSwapChainImageView.Get();
        }

        [[nodiscard]] VulkanGraphicsFence* GetWaitForExecuteCompletionFence() const noexcept
        {
            return _waitForExecuteCompletionFence;
        }

        [[nodiscard]] std::unique_ptr<VulkanGraphicsCmdList> BeginFrame();
        void EndFrame() const;

        void RegisterDescriptorSetForFrame(VulkanGraphicsPipelineSignature* signature, VulkanGraphicsDescriptorSet* set);

        void ResetContext();

        ~VulkanGraphicsContext();
    };
}
