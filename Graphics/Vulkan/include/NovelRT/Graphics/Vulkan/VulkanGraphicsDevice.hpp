#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <cstdint>
#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapter;
    class VulkanShaderProgram;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;

    class VulkanGraphicsDevice
    {
    private:
        VulkanGraphicsAdapter* _adapter;
        VulkanGraphicsSurfaceContext* _surfaceContext;

        NovelRT::Utilities::Lazy<VulkanGraphicsFence*> _presentCompletionFence;
        uint32_t _contextCount;
        NovelRT::Utilities::Lazy<std::vector<VulkanGraphicsContext*>> _contexts;

        LoggingService _logger;

        VkSurfaceKHR _surface;

        NovelRT::Utilities::Lazy<VkDevice> _device;

        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        size_t _contextIndex;
        VkFormat _vulkanSwapChainFormat;
        VkExtent2D _swapChainExtent;

        bool _isAttachedToResizeEvent;

        NovelRT::Utilities::Lazy<VkSwapchainKHR> _vulkanSwapchain;
        NovelRT::Utilities::Lazy<std::vector<VkImage>> _swapChainImages;
        NovelRT::Utilities::Lazy<VulkanGraphicsRenderPass*> _renderPass;

        QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        [[nodiscard]] std::vector<VulkanGraphicsContext*> CreateInitialGraphicsContexts(uint32_t contextCount);
        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] std::vector<std::string> GetFinalPhysicalDeviceExtensionSet() const;

        VkDevice CreateLogicalDevice();

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        VkSwapchainKHR CreateSwapChain(VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);
        std::vector<VkImage> GetSwapChainImages();

        VkRenderPass CreateRenderPass();

    public:
        VulkanGraphicsDevice(VulkanGraphicsAdapter* adapter,
                             VulkanGraphicsSurfaceContext* surfaceContext,
                             int32_t contextCount);

        ~VulkanGraphicsDevice();

        void TearDown();
        size_t GetContextIndex() const noexcept;

        void PresentFrame();

        void Signal(VulkanGraphicsFence* fence) const;

        void WaitForIdle();

        //NOLINTBEGIN(readability-identifier-naming) - stdlib compatibility
        std::vector<VulkanGraphicsContext*>::iterator begin() noexcept;
        std::vector<VulkanGraphicsContext*>::iterator end() noexcept;
        //NOLINTEND(readability-identifier-naming)

        [[nodiscard]] VulkanGraphicsContext* GetCurrentContext();

        [[nodiscard]] VulkanGraphicsSurfaceContext* GetSurfaceContext() const noexcept
        {
            return _surfaceContext;
        }
        [[nodiscard]] IGraphicsSurface* GetSurface() const noexcept;

        [[nodiscard]] VulkanGraphicsAdapter* GetAdapter() const noexcept
        {
            return _adapter;
        }

        [[nodiscard]] std::unique_ptr<VulkanShaderProgram> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> byteData);

        [[nodiscard]] std::unique_ptr<VulkanGraphicsPipeline> CreatePipeline(
            VulkanGraphicsPipelineSignature* signature,
            VulkanShaderProgram* vertexShader,
            VulkanShaderProgram* pixelShader,
            bool imguiRenderMode);

        [[nodiscard]] std::unique_ptr<VulkanGraphicsPipelineSignature> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges);

        [[nodiscard]] VulkanGraphicsRenderPass* GetRenderPass()
        {
            return _renderPass.Get();
        }

        [[nodiscard]] VkSwapchainKHR GetVulkanSwapchain()
        {
            return _vulkanSwapchain.Get();
        }

        [[nodiscard]] VkQueue GetVulkanPresentQueue() const noexcept
        {
            return _presentQueue;
        }

        [[nodiscard]] VkQueue GetVulkanGraphicsQueue() const noexcept
        {
            return _graphicsQueue;
        }

        [[nodiscard]] VkDevice GetVulkanDevice()
        {
            return _device.Get();
        }

        [[nodiscard]] VkRenderPass GetVulkanRenderPass()
        {
            return _renderPass.Get()->GetVulkanRenderPass();
        }

        [[nodiscard]] VkExtent2D GetSwapChainExtent() const noexcept
        {
            return _swapChainExtent;
        }

        [[nodiscard]] const QueueFamilyIndices& GetIndicesData() const noexcept
        {
            return _indicesData;
        }

        [[nodiscard]] const std::vector<VkImage>& GetVulkanSwapChainImages()
        {
            return _swapChainImages.Get();
        }

        [[nodiscard]] VkFormat GetVulkanSwapChainFormat() const noexcept
        {
            return _vulkanSwapChainFormat;
        }

        [[nodiscard]] VulkanGraphicsFence* GetPresentCompletionFence()
        {
            return _presentCompletionFence.Get();
        }

        void ResizeGraphicsContexts(uint32_t newContextCount);
    };
}
