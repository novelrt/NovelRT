// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    using namespace NovelRT::Utilities;

    VulkanGraphicsDescriptorSet::VulkanGraphicsDescriptorSet(VulkanGraphicsPipeline* targetPipeline) noexcept
        :  _descriptorSetHandle(VK_NULL_HANDLE)
        , _pipeline(targetPipeline)
        , _inputResourceRegions{}
    {
        _descriptorSetHandle = _pipeline->GetSignature()->GetDescriptorSetHandle();
    }

    VulkanGraphicsDescriptorSet::~VulkanGraphicsDescriptorSet()
    {
        std::array<VkDescriptorSet, 1> fuck = {_descriptorSetHandle};
        _pipeline->GetSignature()->DestroyDescriptorSets(fuck);
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionToInputs(const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>* region)
    {
        _inputResourceRegions.emplace_back(region);
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionsToInputs(Span<const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>*> regions)
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
                const auto* inputResourceRegion = _inputResourceRegions[index];

                VkWriteDescriptorSet writeDescriptorSet{};

                auto* resource = inputResourceRegion->GetOwningResource();
                if (auto* buffer = dynamic_cast<VulkanGraphicsBuffer*>(resource))
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
                else if (auto* texture = dynamic_cast<VulkanGraphicsTexture*>(resource))
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

template class NovelRT::Graphics::GraphicsDescriptorSet<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
