// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H
#define NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsPipelineSignature final : public GraphicsPipelineSignature
    {

        NovelRT::Utilities::Lazy<VkDescriptorPool> _vulkanDescriptorPool;
        NovelRT::Utilities::Lazy<VkDescriptorSet> _vulkanDescriptorSet;
        NovelRT::Utilities::Lazy<VkDescriptorSetLayout> _vulkanDescriptorSetLayout;
        NovelRT::Utilities::Lazy<VkPipelineLayout> _vulkanPipelineLayout;

        [[nodiscard]] VkDescriptorPool CreateDescriptorPool();
        [[nodiscard]] VkDescriptorSet CreateDescriptorSet();
        [[nodiscard]] VkDescriptorSetLayout CreateDescriptorSetLayout();
        [[nodiscard]] VkPipelineLayout CreatePipelineLayout();

        void DestroyDescriptorPool();
        void DestroyDescriptorSet();
        void DestroyDescriptorSetLayout();
        void DestroyPipelineLayout();

        [[nodiscard]] VkShaderStageFlags GetVulkanShaderStageFlags(ShaderProgramVisibility shaderVisibility) const noexcept;

    public:
        VulkanGraphicsPipelineSignature(std::shared_ptr<VulkanGraphicsDevice> device,
                                        gsl::span<const GraphicsPipelineInput> inputs,
                                        gsl::span<const GraphicsPipelineResource> resources) noexcept;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsPipelineSignature::GetDevice());
        }

        [[nodiscard]] inline VkDescriptorPool GetVulkanDescriptorPool()
        {
            return _vulkanDescriptorPool.getActual();
        }

        [[nodiscard]] inline VkDescriptorSet GetVulkanDescriptorSet()
        {
            return _vulkanDescriptorSet.getActual();
        }

        [[nodiscard]] inline VkDescriptorSetLayout GetVulkanDescriptorSetLayout()
        {
            return _vulkanDescriptorSetLayout.getActual();
        }

        [[nodiscard]] inline VkPipelineLayout GetVulkanPipelineLayout()
        {
            return _vulkanPipelineLayout.getActual();
        }

        ~VulkanGraphicsPipelineSignature() final;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H
