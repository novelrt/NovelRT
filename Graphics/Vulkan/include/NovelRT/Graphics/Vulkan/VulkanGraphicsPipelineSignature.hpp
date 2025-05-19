#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsDevice;

    class VulkanGraphicsPipelineSignature
    {
        VulkanGraphicsDevice* _device;
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;
        std::vector<GraphicsPushConstantRange> _pushConstantRanges;

        mutable NovelRT::Utilities::Lazy<VkDescriptorPool> _vulkanDescriptorPool;
        mutable NovelRT::Utilities::Lazy<VkDescriptorSetLayout> _vulkanDescriptorSetLayout;
        mutable NovelRT::Utilities::Lazy<VkPipelineLayout> _vulkanPipelineLayout;

        [[nodiscard]] VkDescriptorPool CreateDescriptorPool() const;
        [[nodiscard]] VkDescriptorSet CreateDescriptorSetImpl() const;
        [[nodiscard]] VkDescriptorSetLayout CreateDescriptorSetLayout() const;
        [[nodiscard]] VkPipelineLayout CreatePipelineLayout() const;

        void DestroyDescriptorPool();
        void DestroyDescriptorSetLayout();
        void DestroyPipelineLayout();

    public:
        VulkanGraphicsPipelineSignature(
            VulkanGraphicsDevice* device,
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept;

        ~VulkanGraphicsPipelineSignature();

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const
        {
            return _device;
        }

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept
        {
            return _srcBlendFactor;
        }

        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept
        {
            return _dstBlendFactor;
        }

        [[nodiscard]] std::vector<GraphicsPipelineInput> GetInputs() const noexcept
        {
            return _inputs;
        }

        [[nodiscard]] VkDescriptorPool GetVulkanDescriptorPool() const
        {
            return _vulkanDescriptorPool.Get();
        }

        [[nodiscard]] VkDescriptorSet GetDescriptorSetHandle()
        {
            return CreateDescriptorSetImpl();
        }

        [[nodiscard]] std::unique_ptr<VulkanGraphicsDescriptorSet> CreateDescriptorSet()
        {
            // TODO: this
            return nullptr;
        }


        [[nodiscard]] VkDescriptorSetLayout GetVulkanDescriptorSetLayout() const
        {
            return _vulkanDescriptorSetLayout.Get();
        }

        [[nodiscard]] VkPipelineLayout GetVulkanPipelineLayout() const
        {
            return _vulkanPipelineLayout.Get();
        }

        NovelRT::Utilities::Span<const GraphicsPipelineResource> GetResources()
            const noexcept
        {
            return { _resources };
        }

        void DestroyDescriptorSets(NovelRT::Utilities::Span<VkDescriptorSet> vulkanDescriptorSets);
    };
}
