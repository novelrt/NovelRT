// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H
#define NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsPipelineSignature : public GraphicsPipelineSignature
    {
    private:
        Utilities::Lazy<VkDescriptorPool> _vulkanDescriptorPool;
        Utilities::Lazy<VkDescriptorSet> _vulkanDescriptorSet;
        Utilities::Lazy<VkDescriptorSetLayout> _vulkanDescriptorSetLayout;
        Utilities::Lazy<VkPipelineLayout> _vulkanPipelineLayout;

        [[nodiscard]] VkDescriptorPool CreateDescriptorPool();
        [[nodiscard]] VkDescriptorSet CreateDescriptorSet();
        [[nodiscard]] VkDescriptorSetLayout CreateDescriptorSetLayout();
        [[nodiscard]] VkPipelineLayout CreatePipelineLayout();

        void DestroyDescriptorPool();
        void DestroyDescriptorSet();
        void DestroyDescriptorSetLayout();
        void DestroyPipelineLayout();

    public:
        VulkanGraphicsPipelineSignature(std::shared_ptr<VulkanGraphicsDevice> device,
                                        gsl::span<const GraphicsPipelineInput> inputs,
                                        gsl::span<const GraphicsPipelineResource> resources) noexcept;

        [[nodiscard]] inline VkDescriptorPool GetDescriptorPool()
        {
            return _vulkanDescriptorPool.getActual();
        }

        [[nodiscard]] inline VkDescriptorSet GetDescriptorSet()
        {
            return _vulkanDescriptorSet.getActual();
        }

        [[nodiscard]] inline VkDescriptorSetLayout GetDescriptorSetLayout()
        {
            _vulkanDescriptorSetLayout.getActual();
        }

        [[nodiscard]] inline VkPipelineLayout GetPipelineLayout()
        {
            return _vulkanPipelineLayout.getActual();
        }

        ~VulkanGraphicsPipelineSignature();
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSPIPELINESIGNATURE_H
