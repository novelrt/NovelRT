#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline;
    class VulkanGraphicsResource;

    class VulkanGraphicsDescriptorSet
    {
    private:
        VkDescriptorSet _descriptorSetHandle;
        VulkanGraphicsPipeline* _pipeline;
        std::vector<const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>*> _inputResourceRegions;


    public:
        explicit VulkanGraphicsDescriptorSet(VulkanGraphicsPipeline* targetPipeline) noexcept;

        ~VulkanGraphicsDescriptorSet();

        [[nodiscard]] VkDescriptorSet GetVulkanDescriptorSet() const noexcept
        {
            return _descriptorSetHandle;
        }

        [[nodiscard]] VulkanGraphicsPipeline* GetPipeline() const noexcept
        {
            return _pipeline;
        }

        void AddMemoryRegionToInputs(const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>* region);

        void AddMemoryRegionsToInputs(NovelRT::Utilities::Span<const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>*> regions);

        void UpdateDescriptorSetData();
    };
}
