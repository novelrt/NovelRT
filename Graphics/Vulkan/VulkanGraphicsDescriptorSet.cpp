// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan
{
    using namespace NovelRT::Utilities;

    VulkanGraphicsDescriptorSet::VulkanGraphicsDescriptorSet(
        std::shared_ptr<VulkanGraphicsPipeline> targetPipeline) noexcept
        : _pipeline(targetPipeline), _inputResourceRegions{}, _descriptorSetHandle(VK_NULL_HANDLE)
    {
        _descriptorSetHandle = _pipeline->GetSignature()->GenerateVulkanDescriptorSet();
    }

    VulkanGraphicsDescriptorSet::~VulkanGraphicsDescriptorSet()
    {
        std::array<VkDescriptorSet, 1> fuck = {_descriptorSetHandle};
        _pipeline->GetSignature()->DestroyDescriptorSets(fuck);
    }

    const VkDescriptorSet* VulkanGraphicsDescriptorSet::GetVulkanDescriptorSet() const noexcept
    {
        return &_descriptorSetHandle;
    }

    std::shared_ptr<VulkanGraphicsPipeline> VulkanGraphicsDescriptorSet::GetPipeline() const noexcept
    {
        return _pipeline;
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionToInputs(
        std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> region)
    {
        _inputResourceRegions.emplace_back(region);
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionsToInputs(
        Misc::Span<const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>>> regions)
    {
        _inputResourceRegions.insert(_inputResourceRegions.end(), regions.begin(), regions.end());
    }

    void VulkanGraphicsDescriptorSet::UpdateDescriptorSetData()
    {
        if (_descriptorSetHandle != VK_NULL_HANDLE)
        {
            size_t inputResourcesLength = _inputResourceRegions.size();

            for (size_t index = 0; index < inputResourcesLength; index++)
            {
                const auto inputResourceRegion = _inputResourceRegions[index];

                VkWriteDescriptorSet writeDescriptorSet{};

                std::shared_ptr<VulkanGraphicsBuffer> buffer =
                    std::dynamic_pointer_cast<VulkanGraphicsBuffer>(inputResourceRegion->GetOwningResource());
                std::shared_ptr<VulkanGraphicsTexture> texture =
                    std::dynamic_pointer_cast<VulkanGraphicsTexture>(inputResourceRegion->GetOwningResource());

                if (buffer != nullptr)
                {
                    VkDescriptorBufferInfo descriptorBufferInfo{};
                    descriptorBufferInfo.buffer = buffer->GetVulkanBuffer();
                    descriptorBufferInfo.offset = inputResourceRegion->GetOffset();
                    descriptorBufferInfo.range = inputResourceRegion->GetSize();

                    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    writeDescriptorSet.dstSet = _descriptorSetHandle;
                    writeDescriptorSet.dstBinding = static_cast<uint32_t>(index);
                    writeDescriptorSet.descriptorCount = 1;
                    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;

                    vkUpdateDescriptorSets(_pipeline->GetDevice()->GetVulkanDevice(), 1, &writeDescriptorSet, 0,
                                           nullptr);
                }
                else if (texture != nullptr)
                {
                    VkDescriptorImageInfo descriptorImageInfo{};
                    descriptorImageInfo.sampler = texture->GetOrCreateVulkanSampler();
                    descriptorImageInfo.imageView = texture->GetOrCreateVulkanImageView();
                    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

                    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    writeDescriptorSet.dstSet = _descriptorSetHandle;
                    writeDescriptorSet.dstBinding = static_cast<uint32_t>(index);
                    writeDescriptorSet.descriptorCount = 1;
                    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    writeDescriptorSet.pImageInfo = &descriptorImageInfo;

                    vkUpdateDescriptorSets(_pipeline->GetDevice()->GetVulkanDevice(), 1, &writeDescriptorSet, 0,
                                           nullptr);
                }
                else
                {
                    throw std::runtime_error("HOW DID YOU EVEN GET HERE?");
                }
            }
        }
    }
}