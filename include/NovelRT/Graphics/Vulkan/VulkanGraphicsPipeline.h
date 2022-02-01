// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPIPELINE_H
#define NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPIPELINE_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline : public GraphicsPipeline
    {
    private:
        NovelRT::Utilities::Lazy<VkPipeline> _vulkanPipeline;
        [[nodiscard]] VkPipeline CreateVulkanPipeline();
        [[nodiscard]] size_t GetInputElementsCount(gsl::span<const GraphicsPipelineInput> inputs) const noexcept;
        [[nodiscard]] VkFormat GetInputElementFormat(std::type_index index) const noexcept;

    public:
        VulkanGraphicsPipeline(std::shared_ptr<VulkanGraphicsDevice> device,
                               std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
                               std::shared_ptr<VulkanShaderProgram> vertexShader,
                               std::shared_ptr<VulkanShaderProgram> pixelShader) noexcept;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsPipeline::GetDevice());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanShaderProgram> GetPixelShader() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanShaderProgram>(GraphicsPipeline::GetPixelShader());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanShaderProgram> GetVertexShader() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanShaderProgram>(GraphicsPipeline::GetVertexShader());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsPipelineSignature> GetSignature() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsPipelineSignature>(GraphicsPipeline::GetSignature());
        }

        [[nodiscard]] inline VkPipeline GetVulkanPipeline()
        {
            return _vulkanPipeline.getActual();
        }
    };
}

#endif // NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPIPELINE_H
