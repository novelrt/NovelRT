#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <cstdint>
#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsDevice<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsDevice<Vulkan::VulkanGraphicsBackend>>
    {
    public:
        using iterator = typename std::vector<std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>>::iterator;
        using const_iterator = typename std::vector<std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>>::const_iterator;

    private:
        std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> _adapter;
        std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> _surfaceContext;

        NovelRT::Utilities::Lazy<std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>>> _presentCompletionFence;

        uint32_t _contextCount;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>>> _contexts;

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
        NovelRT::Utilities::Lazy<std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>>> _renderPass;

        Vulkan::QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        [[nodiscard]] std::vector<std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>> CreateInitialGraphicsContexts(uint32_t contextCount);

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] std::vector<std::string> GetFinalPhysicalDeviceExtensionSet(std::vector<std::string> requiredDeviceExtensions, std::vector<std::string> optionalDeviceExtensions) const;
        VkDevice CreateLogicalDevice(std::vector<std::string> requiredDeviceExtensions, std::vector<std::string> optionalDeviceExtensions);

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        VkSwapchainKHR CreateSwapChain(VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);
        std::vector<VkImage> GetSwapChainImages();

        VkRenderPass CreateRenderPass();

        void ResizeGraphicsContexts(int32_t newContextCount);

    public:
        GraphicsDevice(std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> adapter,
                       std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> surfaceContext,
                       int32_t contextCount,
                       std::vector<std::string> requiredDeviceExtensions, std::vector<std::string> optionalDeviceExtensions);

        ~GraphicsDevice();

        [[nodiscard]] std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> GetAdapter() const;

        size_t GetContextIndex() const noexcept;

        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() noexcept;
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator begin() const noexcept;
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() noexcept;
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator end() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> GetCurrentContext() const;

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> GetSurfaceContext() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> signature,
            std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> vertexShader,
            std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> pixelShader,
            bool imguiRenderMode);

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges);

        [[nodiscard]] std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>> GetRenderPass();
        [[nodiscard]] std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>> GetRenderPass() const;

        [[nodiscard]] std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> byteData);

        void PresentFrame();

        void Signal(const GraphicsFence<Vulkan::VulkanGraphicsBackend>* fence);

        void WaitForIdle();

        [[nodiscard]] VkSwapchainKHR GetVulkanSwapchain() const;
        [[nodiscard]] VkQueue GetVulkanPresentQueue() const noexcept;
        [[nodiscard]] VkQueue GetVulkanGraphicsQueue() const noexcept;
        [[nodiscard]] VkDevice GetVulkanDevice() const;
        [[nodiscard]] VkRenderPass GetVulkanRenderPass() const;
        [[nodiscard]] VkExtent2D GetSwapChainExtent() const noexcept;
        [[nodiscard]] VkFormat GetVulkanSwapChainFormat() const noexcept;

        [[nodiscard]] std::vector<VkImage> GetVulkanSwapChainImages() const;

        [[nodiscard]] const Vulkan::QueueFamilyIndices& GetIndicesData() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> GetPresentCompletionFence() const;
    };
}
