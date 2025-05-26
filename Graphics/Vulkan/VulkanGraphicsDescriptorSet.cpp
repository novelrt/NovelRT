// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsBuffer = GraphicsBuffer<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;

    VulkanGraphicsDescriptorSet::GraphicsDescriptorSet(
        std::shared_ptr<VulkanGraphicsPipeline> targetPipeline,
        VkDescriptorSet descriptorSetHandle) noexcept
        :  _descriptorSetHandle(descriptorSetHandle)
        , _pipeline(std::move(targetPipeline))
        , _inputResourceRegions{}
    { }

    VulkanGraphicsDescriptorSet::~GraphicsDescriptorSet()
    {
        auto device = _pipeline->GetDevice().lock();
        auto signature = _pipeline->GetSignature().lock();
        vkFreeDescriptorSets(device->GetVulkanDevice(), signature->GetVulkanDescriptorPool(), 1, &_descriptorSetHandle);
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionToInputs(const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsResource>>& region)
    {
        _inputResourceRegions.emplace_back(region);
    }

    void VulkanGraphicsDescriptorSet::AddMemoryRegionsToInputs(Utilities::Span<std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsResource>>> regions)
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
                auto inputResourceRegion = _inputResourceRegions[index];

                VkWriteDescriptorSet writeDescriptorSet{};

                auto resource = inputResourceRegion->GetOwningResource().lock();
                auto device = _pipeline->GetDevice().lock();
                if (auto buffer = std::dynamic_pointer_cast<VulkanGraphicsBuffer>(resource))
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

                    vkUpdateDescriptorSets(device->GetVulkanDevice(), 1, &writeDescriptorSet, 0,
                                           nullptr);
                }
                else if (auto texture = std::dynamic_pointer_cast<VulkanGraphicsTexture>(resource))
                {
                    VkDescriptorImageInfo descriptorImageInfo{};
                    descriptorImageInfo.sampler = texture->GetVulkanSampler();
                    descriptorImageInfo.imageView = texture->GetVulkanImageView();
                    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

                    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    writeDescriptorSet.dstSet = _descriptorSetHandle;
                    writeDescriptorSet.dstBinding = static_cast<uint32_t>(index);
                    writeDescriptorSet.descriptorCount = 1;
                    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    writeDescriptorSet.pImageInfo = &descriptorImageInfo;

                    vkUpdateDescriptorSets(device->GetVulkanDevice(), 1, &writeDescriptorSet, 0,
                                           nullptr);
                }
                else
                {
                    throw std::runtime_error("HOW DID YOU EVEN GET HERE?");
                }
            }
        }
    }

    VkDescriptorSet VulkanGraphicsDescriptorSet::GetVulkanDescriptorSet() const noexcept
    {
        return _descriptorSetHandle;
    }

    std::weak_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsDescriptorSet::GetPipeline() const noexcept
    {
        return _pipeline;
    }
}
