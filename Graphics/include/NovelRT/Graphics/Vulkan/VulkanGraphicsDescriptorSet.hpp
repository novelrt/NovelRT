#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline;
    class VulkanGraphicsResource;

    class VulkanGraphicsDescriptorSet 
    {
    private:
        VkDescriptorSet _descriptorSetHandle;
        std::shared_ptr<VulkanGraphicsPipeline> _pipeline;
        std::vector<std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>>> _inputResourceRegions;
        

    public:
        explicit VulkanGraphicsDescriptorSet(std::shared_ptr<VulkanGraphicsPipeline> targetPipeline) noexcept;

        ~VulkanGraphicsDescriptorSet();

        [[nodiscard]] const VkDescriptorSet* GetVulkanDescriptorSet() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPipeline> GetPipeline() const noexcept;

        void AddMemoryRegionToInputs(std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> region);
        
        void AddMemoryRegionsToInputs(NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>>> regions);

        void UpdateDescriptorSetData();
    };
}