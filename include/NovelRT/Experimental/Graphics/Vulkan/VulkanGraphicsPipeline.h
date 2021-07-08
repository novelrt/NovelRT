// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSPIPELINE_H
#define NOVELRT_VULKANGRAPHICSPIPELINE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsPipeline : public GraphicsPipeline
    {
    private:
        Utilities::Lazy<VkPipeline> _vulkanPipeline;
        [[nodiscard]] VkPipeline CreateVulkanPipeline();
        [[nodiscard]] size_t GetInputElementsCount(gsl::span<const GraphicsPipelineInput> inputs) const noexcept;
        [[nodiscard]] VkFormat GetInputElementFormat(std::type_index index) const noexcept;

    public:
        VulkanGraphicsPipeline(std::shared_ptr<VulkanGraphicsDevice> device,
                               std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
                               std::shared_ptr<VulkanShaderProgram> vertexShader,
                               std::shared_ptr<VulkanShaderProgram> pixelShader) noexcept;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSPIPELINE_H
