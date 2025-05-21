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
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

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
        GraphicsPipelineSignature(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept;

        ~GraphicsPipelineSignature() = default;

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept;
        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept;

        [[nodiscard]] std::vector<GraphicsPipelineInput> GetInputs() const noexcept;

        [[nodiscard]] VkDescriptorPool GetVulkanDescriptorPool() const;

        [[nodiscard]] VkDescriptorSet GetDescriptorSetHandle();

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>> CreateDescriptorSet();


        [[nodiscard]] VkDescriptorSetLayout GetVulkanDescriptorSetLayout() const;

        [[nodiscard]] VkPipelineLayout GetVulkanPipelineLayout() const;

        NovelRT::Utilities::Span<const GraphicsPipelineResource> GetResources() const noexcept;

        void DestroyDescriptorSets(NovelRT::Utilities::Span<VkDescriptorSet> vulkanDescriptorSets);
    };
}
