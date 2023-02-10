// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSDEVICE_H
#define NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSDEVICE_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice final : public GraphicsDevice
    {
    private:
        NovelRT::Utilities::Lazy<std::shared_ptr<VulkanGraphicsFence>> _presentCompletionFence;
        uint32_t _contextCount;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<VulkanGraphicsContext>>> _contexts;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsContext>>> _contextPtrs;

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
        NovelRT::Utilities::Lazy<std::shared_ptr<VulkanGraphicsMemoryAllocator>> _memoryAllocator;

        QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        [[nodiscard]] std::vector<std::shared_ptr<VulkanGraphicsContext>> CreateGraphicsContexts(uint32_t contextCount);
        [[nodiscard]] std::shared_ptr<VulkanGraphicsMemoryAllocator> CreateMemoryAllocator();
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

    protected:
        VulkanGraphicsMemoryAllocator* GetMemoryAllocatorInternal() final;

    public:
        VulkanGraphicsDevice(const std::shared_ptr<VulkanGraphicsAdapter>& adapter,
                             const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext,
                             int32_t contextCount);

        void TearDown() final;
        size_t GetContextIndex() const noexcept override;

        std::shared_ptr<GraphicsPrimitive> CreatePrimitive(
            std::shared_ptr<GraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
            uint32_t indexBufferStride,
            NovelRT::Utilities::Misc::Span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions) final;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPrimitive> CreateVulkanPrimitive(
            std::shared_ptr<VulkanGraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
            uint32_t indexBufferStride,
            NovelRT::Utilities::Misc::Span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions);

        void PresentFrame() final;

        void Signal(std::shared_ptr<GraphicsFence> fence) final;
        void SignalVulkan(const std::shared_ptr<VulkanGraphicsFence>& fence) const;

        void WaitForIdle() final;

        [[nodiscard]] inline NovelRT::Utilities::Misc::Span<std::shared_ptr<GraphicsContext>> GetContexts() final
        {
            return NovelRT::Utilities::Misc::Span<std::shared_ptr<GraphicsContext>>(
                &(*_contextPtrs.getActual().begin()), _contextPtrs.getActual().size());
        }

        [[nodiscard]] std::shared_ptr<VulkanGraphicsContext> GetCurrentContext()
        {
            return std::dynamic_pointer_cast<VulkanGraphicsContext>(GetContexts()[GetContextIndex()]);
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsAdapter> GetAdapter() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsAdapter>(GraphicsDevice::GetAdapter());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsSurfaceContext> GetSurfaceContext() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsSurfaceContext>(GraphicsDevice::GetSurfaceContext());
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Misc::Span<uint8_t> byteData) final;

        [[nodiscard]] std::shared_ptr<GraphicsPipeline> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature> signature,
            std::shared_ptr<ShaderProgram> vertexShader,
            std::shared_ptr<ShaderProgram> pixelShader) final;

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineResource> resources) final;

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

        std::vector<std::shared_ptr<GraphicsContext>> CreateGraphicsContextPointers();
        void ResizeGraphicsContexts(uint32_t newContextCount);

        ~VulkanGraphicsDevice() final;
    };
}

#endif // NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSDEVICE_H
