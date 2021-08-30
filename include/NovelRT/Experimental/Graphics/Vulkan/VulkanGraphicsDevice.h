// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSDEVICE_H
#define NOVELRT_VULKANGRAPHICSDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsDevice final : public GraphicsDevice
    {
    private:
        std::vector<VulkanGraphicsContext> _contexts;
        std::vector<std::shared_ptr<const GraphicsContext>> _contextPtrs;
        VulkanGraphicsFence _fence;

        LoggingService _logger;

        VkDevice _device;

        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        VkSurfaceKHR _surface;

        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        size_t _contextIndex;
        VkFormat _vulkanSwapChainFormat;
        VkExtent2D _swapChainExtent;

        NovelRT::Utilities::Lazy<VkRenderPass> _renderPass;
        NovelRT::Utilities::Lazy<VulkanGraphicsMemoryAllocator> _memoryAllocator;

        QueueFamilyIndices _indicesData;

        Threading::VolatileState _state;

        [[nodiscard]] std::vector<VulkanGraphicsContext> CreateGraphicsContexts(int32_t contextCount) const;

        void Initialise();

        [[nodiscard]] std::vector<std::string> GetFinalPhysicalDeviceExtensionSet() const;
        [[nodiscard]] bool CheckPhysicalDeviceRequiredExtensionSupport(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] int32_t GetPhysicalDeviceOptionalExtensionSupportScore(
            VkPhysicalDevice physicalDevice) const noexcept;

        void ConfigureOutputSurface(std::shared_ptr<IGraphicsSurface> targetSurface);

        [[nodiscard]] QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] int32_t RateDeviceSuitability(VkPhysicalDevice physicalDevice) const noexcept;

        void CreateLogicalDevice();

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(
            const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        void CreateSwapChain();

        VkRenderPass CreateRenderPass();

    protected:
        VulkanGraphicsMemoryAllocator* GetMemoryAllocatorInternal() final;

    public:
        VulkanGraphicsDevice(std::shared_ptr<VulkanGraphicsAdapter> adapter,
                             std::shared_ptr<IGraphicsSurface> surface,
                             int32_t contextCount);
        void TearDown() final;

        size_t GetContextIndex() const noexcept override;

        std::shared_ptr<GraphicsPrimitive> CreatePrimitive(
            std::shared_ptr<GraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
            uint32_t indexBufferStride,
            gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions) final;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPrimitive> CreateVulkanPrimitive(
            std::shared_ptr<VulkanGraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
            uint32_t indexBufferStride,
            gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions);

        void PresentFrame() final;
        void Signal(std::shared_ptr<GraphicsFence> fence) final;
        void WaitForIdle() final;

        [[nodiscard]] inline gsl::span<std::shared_ptr<const GraphicsContext>> GetContexts() final
        {
            return gsl::span<std::shared_ptr<const GraphicsContext>>(&(*_contextPtrs.begin()), _contextPtrs.size());
        }

        [[nodiscard]] std::shared_ptr<const VulkanGraphicsContext> GetCurrentContext()
        {
            return std::dynamic_pointer_cast<const VulkanGraphicsContext>(GetContexts()[GetContextIndex()]);
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsAdapter> GetAdapter() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsAdapter>(GraphicsDevice::GetAdapter());
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram> CreateShaderProgram(std::string entryPointName,
                                                                         ShaderProgramKind kind,
                                                                         gsl::span<uint8_t> byteData) final;

        [[nodiscard]] std::shared_ptr<GraphicsPipeline> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature> signature,
            std::shared_ptr<ShaderProgram> vertexShader = nullptr,
            std::shared_ptr<ShaderProgram> pixelShader = nullptr) final;

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            gsl::span<GraphicsPipelineInput> inputs = gsl::span<GraphicsPipelineInput>{},
            gsl::span<GraphicsPipelineResource> resources = gsl::span<GraphicsPipelineResource>{}) final;

        ~VulkanGraphicsDevice();

        [[nodiscard]] inline VkDevice GetVulkanDevice() const noexcept
        {
            return _device;
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

        [[nodiscard]] inline const std::vector<VkImage>& GetVulkanSwapChainImages() const noexcept
        {
            return _swapChainImages;
        }

        [[nodiscard]] inline VkFormat GetVulkanSwapChainFormat() const noexcept
        {
            return _vulkanSwapChainFormat;
        }
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSDEVICE_H
