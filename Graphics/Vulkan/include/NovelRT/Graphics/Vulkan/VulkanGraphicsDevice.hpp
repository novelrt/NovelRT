#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsSwapchain.hpp>
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
    private:
        std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> _adapter;
        std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> _surfaceContext;

        NovelRT::Utilities::Lazy<std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>>> _presentCompletionFence;

        Logging::LoggingService _logger;

        VkSurfaceKHR _surface;

        NovelRT::Utilities::Lazy<VkDevice> _device;

        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        bool _isAttachedToResizeEvent;

        NovelRT::Utilities::Lazy<std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>>> _vulkanSwapchain;

        Vulkan::QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] std::vector<std::string> GetFinalPhysicalDeviceExtensionSet(
            std::vector<std::string> requiredDeviceExtensions,
            std::vector<std::string> optionalDeviceExtensions) const;
        VkDevice CreateLogicalDevice(std::vector<std::string> requiredDeviceExtensions,
                                     std::vector<std::string> optionalDeviceExtensions);

    public:
        GraphicsDevice(std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> adapter,
                       std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> surfaceContext,
                       std::vector<std::string> requiredDeviceExtensions,
                       std::vector<std::string> optionalDeviceExtensions);

        ~GraphicsDevice();

        [[nodiscard]] std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>> GetAdapter() const;

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>> GetSurfaceContext()
            const noexcept;

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

        [[nodiscard]] std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> byteData);

        void PresentFrame();

        // TODO: Reimplement the functionality in the source file for this method in the swapchain image.
        void Signal(const std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>>& context);

        void WaitForIdle();

        [[nodiscard]] VkQueue GetVulkanPresentQueue() const noexcept;
        [[nodiscard]] VkQueue GetVulkanGraphicsQueue() const noexcept;
        [[nodiscard]] VkDevice GetVulkanDevice() const;

        [[nodiscard]] const Vulkan::QueueFamilyIndices& GetIndicesData() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsFence<Vulkan::VulkanGraphicsBackend>> GetPresentCompletionFence() const;
    };
}
