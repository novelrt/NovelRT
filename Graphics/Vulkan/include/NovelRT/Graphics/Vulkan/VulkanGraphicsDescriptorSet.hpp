#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
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
    class GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>
        : std::enable_shared_from_this<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        VkDescriptorSet _descriptorSetHandle;
        std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>> _pipeline;
        std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>>> _inputResourceRegions;


    public:
        explicit GraphicsDescriptorSet(
            std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>> targetPipeline,
            VkDescriptorSet descriptorSet) noexcept;
        ~GraphicsDescriptorSet();

        void AddMemoryRegionToInputs(const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>>& region);
        void AddMemoryRegionsToInputs(Utilities::Span<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>>> regions);

        void UpdateDescriptorSetData();

        [[nodiscard]] VkDescriptorSet GetVulkanDescriptorSet() const noexcept;

        [[nodiscard]] std::weak_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>> GetPipeline() const noexcept;
    };
}
