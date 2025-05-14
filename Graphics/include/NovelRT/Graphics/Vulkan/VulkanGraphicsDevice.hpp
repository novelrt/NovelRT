#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <NovelRT/Utilities/Lazy.h>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapter;
    class VulkanShaderProgram;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;

    class VulkanGraphicsDevice : public std::enable_shared_from_this<VulkanGraphicsDevice>
    {
    private:
        std::shared_ptr<VulkanGraphicsAdapter> _adapter;
        std::shared_ptr<VulkanGraphicsSurfaceContext> _surfaceContext;
        NovelRT::Utilities::Lazy<std::shared_ptr<VulkanGraphicsFence>> _presentCompletionFence;
        uint32_t _contextCount;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<VulkanGraphicsContext>>> _contexts;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<VulkanGraphicsContext>>> _contextPtrs;

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
        NovelRT::Utilities::Lazy<VkRenderPass> _renderPass;

        QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        [[nodiscard]] std::vector<std::shared_ptr<VulkanGraphicsContext>> CreateGraphicsContexts(uint32_t contextCount);
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
        VulkanGraphicsDevice(std::shared_ptr<VulkanGraphicsAdapter> adapter,
                             std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
                             int32_t contextCount);

        void TearDown();
        size_t GetContextIndex() const noexcept;

        void PresentFrame();

        void Signal(std::shared_ptr<VulkanGraphicsFence> fence) const;

        void WaitForIdle();

        std::vector<std::shared_ptr<VulkanGraphicsContext>>::iterator begin() noexcept;
        std::vector<std::shared_ptr<VulkanGraphicsContext>>::iterator end() noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsContext> GetCurrentContext();
        [[nodiscard]] std::shared_ptr<VulkanGraphicsSurfaceContext> GetSurfaceContext() const noexcept;

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsAdapter> GetAdapter() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanShaderProgram> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Misc::Span<uint8_t> byteData);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPipeline> CreatePipeline(
            std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
            std::shared_ptr<VulkanShaderProgram> vertexShader,
            std::shared_ptr<VulkanShaderProgram> pixelShader);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPipelineSignature> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineResource> resources);

        [[nodiscard]] inline VkSwapchainKHR GetVulkanSwapchain()
        {
            return _vulkanSwapchain.getActual();
        }

        [[nodiscard]] inline VkQueue GetVulkanPresentQueue() const noexcept
        {
            return _presentQueue;
        }

        [[nodiscard]] inline VkQueue GetVulkanGraphicsQueue() const noexcept
        {
            return _graphicsQueue;
        }

        [[nodiscard]] inline VkDevice GetVulkanDevice()
        {
            return _device.getActual();
        }

        [[nodiscard]] inline VkRenderPass GetVulkanRenderPass()
        {
            return _renderPass.getActual();
        }

        [[nodiscard]] VkExtent2D GetSwapChainExtent() const noexcept
        {
            return _swapChainExtent;
        }

        [[nodiscard]] inline const QueueFamilyIndices& GetIndicesData() const noexcept
        {
            return _indicesData;
        }

        [[nodiscard]] inline const std::vector<VkImage>& GetVulkanSwapChainImages()
        {
            return _swapChainImages.getActual();
        }

        [[nodiscard]] inline VkFormat GetVulkanSwapChainFormat() const noexcept
        {
            return _vulkanSwapChainFormat;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsFence> GetPresentCompletionFence()
        {
            return _presentCompletionFence.getActual();
        }

        std::vector<std::shared_ptr<VulkanGraphicsContext>> CreateGraphicsContextPointers();
        void ResizeGraphicsContexts(uint32_t newContextCount);

        ~VulkanGraphicsDevice();
    };
}
