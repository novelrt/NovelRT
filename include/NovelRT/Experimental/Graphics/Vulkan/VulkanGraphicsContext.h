// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSCONTEXT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSCONTEXT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsContext final : public GraphicsContext
    {
    private:
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
        void BeginCopy() noexcept;
        void EndCopy() noexcept;

    public:
        VulkanGraphicsContext(std::shared_ptr<VulkanGraphicsDevice> device, size_t index) noexcept;

        void OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F newSize);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return std::static_pointer_cast<VulkanGraphicsDevice>(GraphicsContext::GetDevice());
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsFence> GetFence() const noexcept final
        {
            return _fence;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsFence> GetVulkanFence() const noexcept
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

        void BeginDrawing(NovelRT::Graphics::RGBAConfig backgroundColour) final;
        void BeginFrame() final;

        inline void Copy(std::shared_ptr<GraphicsBuffer> destination, std::shared_ptr<GraphicsBuffer> source) final
        {
            Copy(std::static_pointer_cast<VulkanGraphicsBuffer>(destination), std::static_pointer_cast<VulkanGraphicsBuffer>(source));
        }

        inline void Copy(std::shared_ptr<GraphicsTexture> destination, std::shared_ptr<GraphicsBuffer> source) final
        {
            Copy(std::static_pointer_cast<VulkanGraphicsTexture>(destination), std::static_pointer_cast<VulkanGraphicsBuffer>(source));
        }

        void Copy(std::shared_ptr<VulkanGraphicsBuffer> destination, std::shared_ptr<VulkanGraphicsBuffer> source);
        void Copy(std::shared_ptr<VulkanGraphicsTexture> destination, std::shared_ptr<VulkanGraphicsBuffer> source);

        inline void Draw(std::shared_ptr<GraphicsPrimitive> primitive) final
        {
            Draw(std::static_pointer_cast<VulkanGraphicsPrimitive>(primitive));
        }

        void Draw(std::shared_ptr<VulkanGraphicsPrimitive> primitive);
        void EndDrawing() final;
        void EndFrame() final;

        ~VulkanGraphicsContext() final;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSCONTEXT_H
