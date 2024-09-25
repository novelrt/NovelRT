#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;

    class VulkanGraphicsPipelineSignature
    {
        std::shared_ptr<VulkanGraphicsDevice> _device;
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;
        NovelRT::Utilities::Lazy<VkDescriptorPool> _vulkanDescriptorPool;
        NovelRT::Utilities::Lazy<VkDescriptorSetLayout> _vulkanDescriptorSetLayout;
        NovelRT::Utilities::Lazy<VkPipelineLayout> _vulkanPipelineLayout;

        [[nodiscard]] VkDescriptorPool CreateDescriptorPool();
        [[nodiscard]] VkDescriptorSet CreateDescriptorSet();
        [[nodiscard]] VkDescriptorSetLayout CreateDescriptorSetLayout();
        [[nodiscard]] VkPipelineLayout CreatePipelineLayout();

        void DestroyDescriptorPool();
        void DestroyDescriptorSetLayout();
        void DestroyPipelineLayout();

        [[nodiscard]] VkShaderStageFlags GetVulkanShaderStageFlags(
            ShaderProgramVisibility shaderVisibility) const noexcept;

    public:
        VulkanGraphicsPipelineSignature(
            std::shared_ptr<VulkanGraphicsDevice> device,
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> resources) noexcept;
        
        ~VulkanGraphicsPipelineSignature();

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const
        {
            return _device;
        }

        [[nodiscard]] inline GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept
        {
            return _srcBlendFactor;
        }

        [[nodiscard]] inline GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept
        {
            return _dstBlendFactor;
        }

        [[nodiscard]] inline std::vector<GraphicsPipelineInput> GetInputs() const noexcept
        {
            return _inputs;
        }

        [[nodiscard]] inline VkDescriptorPool GetVulkanDescriptorPool()
        {
            return _vulkanDescriptorPool.getActual();
        }

        [[nodiscard]] inline VkDescriptorSet GenerateVulkanDescriptorSet()
        {
            return CreateDescriptorSet();
        }

        [[nodiscard]] inline VkDescriptorSetLayout GetVulkanDescriptorSetLayout()
        {
            return _vulkanDescriptorSetLayout.getActual();
        }

        [[nodiscard]] inline VkPipelineLayout GetVulkanPipelineLayout()
        {
            return _vulkanPipelineLayout.getActual();
        }
        
        NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> GetResources()
            const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource>(&(*_resources.begin()),
                                                                                  _resources.size());
        }

        void DestroyDescriptorSets(NovelRT::Utilities::Misc::Span<VkDescriptorSet> vulkanDescriptorSets);
    };
}
