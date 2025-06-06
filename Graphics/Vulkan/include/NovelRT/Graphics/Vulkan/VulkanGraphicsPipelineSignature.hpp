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
    template<>
    class GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;

        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;
        std::vector<GraphicsPushConstantRange> _pushConstantRanges;

        mutable NovelRT::Utilities::Lazy<VkDescriptorPool> _vulkanDescriptorPool;
        mutable NovelRT::Utilities::Lazy<VkDescriptorSetLayout> _vulkanDescriptorSetLayout;
        mutable NovelRT::Utilities::Lazy<VkPipelineLayout> _vulkanPipelineLayout;

        void DestroyDescriptorPool();
        void DestroyDescriptorSetLayout();
        void DestroyDescriptorSets(NovelRT::Utilities::Span<VkDescriptorSet> vulkanDescriptorSets);
        void DestroyPipelineLayout();

    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsPipelineSignature(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept;

        ~GraphicsPipelineSignature();

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const;

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept;
        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>> CreateDescriptorSet(
            const std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>>& pipeline);

        [[nodiscard]] std::vector<GraphicsPipelineInput> GetInputs() const noexcept;
        [[nodiscard]] std::vector<GraphicsPipelineResource> GetResources() const noexcept;
        [[nodiscard]] std::vector<GraphicsPushConstantRange> GetPushConstantRanges() const noexcept;

        [[nodiscard]] VkDescriptorPool GetVulkanDescriptorPool() const;
        [[nodiscard]] VkDescriptorSetLayout GetVulkanDescriptorSetLayout() const;
        [[nodiscard]] VkPipelineLayout GetVulkanPipelineLayout() const;
    };
}
