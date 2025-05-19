// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp>

#include <NovelRT/Utilities/Operators.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VkDescriptorPool VulkanGraphicsPipelineSignature::CreateDescriptorPool() const
    {
        VkDescriptorPool returnDescriptorPool = VK_NULL_HANDLE;
        std::vector<VkDescriptorPoolSize> vulkanDescriptorPoolSizes{};

        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        descriptorPoolCreateInfo.maxSets = 100;

        auto resources = GetResources();
        size_t resourcesLength = resources.size();

        if (resourcesLength != 0)
        {
            size_t vulkanDescriptorPoolSizesCount = 0;
            size_t constantBufferCount = 0;
            size_t textureCount = 0;

            for (auto&& resource : resources)
            {
                switch (resource.GetKind())
                {
                    case GraphicsPipelineResourceKind::ConstantBuffer:
                    {
                        if (constantBufferCount == 0)
                        {
                            vulkanDescriptorPoolSizesCount++;
                        }
                        constantBufferCount++;
                        break;
                    }

                    case GraphicsPipelineResourceKind::Texture:
                    {
                        if (textureCount == 0)
                        {
                            vulkanDescriptorPoolSizesCount++;
                        }
                        textureCount++;
                        break;
                    }
                    case GraphicsPipelineResourceKind::Unknown:
                    default:
                    {
                        break;
                    }
                }
            }

            vulkanDescriptorPoolSizes.resize(vulkanDescriptorPoolSizesCount);
            size_t vulkanDescriptorPoolSizesIndex = 0;

            if (constantBufferCount != 0)
            {
                VkDescriptorPoolSize newDescriptor{};
                newDescriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                newDescriptor.descriptorCount = static_cast<uint32_t>(constantBufferCount);
                vulkanDescriptorPoolSizes[vulkanDescriptorPoolSizesIndex] = newDescriptor;
                vulkanDescriptorPoolSizesIndex++;
            }

            if (textureCount != 0)
            {
                VkDescriptorPoolSize newDescriptor{};
                newDescriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                newDescriptor.descriptorCount = static_cast<uint32_t>(textureCount);
                vulkanDescriptorPoolSizes[vulkanDescriptorPoolSizesIndex] = newDescriptor;
                vulkanDescriptorPoolSizesIndex++;
            }

            size_t originalSize = vulkanDescriptorPoolSizes.size();
            size_t finalSize = 100 * originalSize;
            vulkanDescriptorPoolSizes.resize(finalSize);

            for (size_t i = originalSize; i < finalSize; i += originalSize)
            {
                VkDescriptorPoolSize* locationToOverwrite = &vulkanDescriptorPoolSizes[i];
                for (size_t j = 0; j < originalSize; j++)
                {
                    locationToOverwrite[j] = vulkanDescriptorPoolSizes[j];
                }
            }

            // TODO: These need to be multiplied by 100 I think. Oh no.
            descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(vulkanDescriptorPoolSizes.size());
            descriptorPoolCreateInfo.pPoolSizes = vulkanDescriptorPoolSizes.data();

            VkResult descriptorPoolResult =
                vkCreateDescriptorPool(GetDevice()->GetVulkanDevice(), &descriptorPoolCreateInfo, nullptr, &returnDescriptorPool);

            if (descriptorPoolResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorPool.",
                                                                 descriptorPoolResult);
            }
        }

        return returnDescriptorPool;
    }

    VkDescriptorSet VulkanGraphicsPipelineSignature::CreateDescriptorSetImpl() const
    {
        VkDescriptorSet returnDescriptorSet = VK_NULL_HANDLE;
        VkDescriptorPool vulkanDescriptorPool = GetVulkanDescriptorPool();

        if (vulkanDescriptorPool != VK_NULL_HANDLE)
        {
            VkDescriptorSetLayout vulkanDescriptorSetLayout = GetVulkanDescriptorSetLayout();

            VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
            descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            descriptorSetAllocateInfo.descriptorPool = vulkanDescriptorPool;
            descriptorSetAllocateInfo.descriptorSetCount = 1;
            descriptorSetAllocateInfo.pSetLayouts = &vulkanDescriptorSetLayout;

            VkResult allocatorDescriptorSetsResult =
                vkAllocateDescriptorSets(GetDevice()->GetVulkanDevice(),
                                         &descriptorSetAllocateInfo, &returnDescriptorSet);

            if (allocatorDescriptorSetsResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorSet.",
                                                                 allocatorDescriptorSetsResult);
            }
        }

        return returnDescriptorSet;
    }

    VkDescriptorSetLayout VulkanGraphicsPipelineSignature::CreateDescriptorSetLayout() const
    {
        VkDescriptorSetLayout vulkanDescriptorSetLayout = VK_NULL_HANDLE;

        std::vector<VkDescriptorSetLayoutBinding> descriptorSetLayoutBindings{};

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

        auto resources = GetResources();
        size_t resourcesLength = resources.size();
        size_t descriptorSetLayoutBindingsIndex = 0;

        if (resourcesLength != 0)
        {
            descriptorSetLayoutBindings.resize(resources.size());

            for (auto&& resource : resources)
            {
                switch (resource.GetKind())
                {
                    case GraphicsPipelineResourceKind::ConstantBuffer:
                    {
                        auto stageFlags = Utilities::GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

                        VkDescriptorSetLayoutBinding descriptorSetLayoutBinding{};
                        descriptorSetLayoutBinding.binding = static_cast<uint32_t>(descriptorSetLayoutBindingsIndex);
                        descriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                        descriptorSetLayoutBinding.descriptorCount = 1;
                        descriptorSetLayoutBinding.stageFlags = stageFlags;

                        descriptorSetLayoutBindings[descriptorSetLayoutBindingsIndex] = descriptorSetLayoutBinding;
                        descriptorSetLayoutBindingsIndex++;
                        break;
                    }
                    case GraphicsPipelineResourceKind::Texture:
                    {
                        auto stageFlags = Utilities::GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

                        VkDescriptorSetLayoutBinding descriptorSetLayoutBinding{};
                        descriptorSetLayoutBinding.binding = static_cast<uint32_t>(descriptorSetLayoutBindingsIndex);
                        descriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                        descriptorSetLayoutBinding.descriptorCount = 1;
                        descriptorSetLayoutBinding.stageFlags = stageFlags;

                        descriptorSetLayoutBindings[descriptorSetLayoutBindingsIndex] = descriptorSetLayoutBinding;
                        descriptorSetLayoutBindingsIndex++;
                        break;
                    }
                    case GraphicsPipelineResourceKind::Unknown:
                    default:
                    {
                        break;
                    }
                }
            }

            descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayoutBindings.size());
            descriptorSetLayoutCreateInfo.pBindings = descriptorSetLayoutBindings.data();

            VkResult descriptorSetLayoutResult = vkCreateDescriptorSetLayout(GetDevice()->GetVulkanDevice(),
                &descriptorSetLayoutCreateInfo, nullptr, &vulkanDescriptorSetLayout);

            if (descriptorSetLayoutResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create the VkDescriptorSetLayout.",
                                                                 descriptorSetLayoutResult);
            }
        }

        return vulkanDescriptorSetLayout;
    }

    VkPipelineLayout VulkanGraphicsPipelineSignature::CreatePipelineLayout() const
    {
        VkPipelineLayout vulkanPipelineLayout = VK_NULL_HANDLE;

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        VkDescriptorSetLayout descriptorSetLayout = GetVulkanDescriptorSetLayout();

        if (descriptorSetLayout != VK_NULL_HANDLE)
        {
            pipelineLayoutCreateInfo.setLayoutCount = 1;
            pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
        }

        std::vector<VkPushConstantRange> finalPushConstantRangeData{};
        if (_pushConstantRanges.size() != 0)
        {
            finalPushConstantRangeData.resize(_pushConstantRanges.size());

            std::transform(_pushConstantRanges.begin(), _pushConstantRanges.end(), finalPushConstantRangeData.begin(),
                           [&](const GraphicsPushConstantRange& rangeData) {
                            VkPushConstantRange returnData{};
                            returnData.stageFlags = Utilities::GetVulkanShaderStageFlags(rangeData.visibilityFlags);
                            returnData.size = static_cast<uint32_t>(rangeData.size);
                            returnData.offset = static_cast<uint32_t>(rangeData.offset);

                            return returnData;
                           });

            pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(finalPushConstantRangeData.size());
            pipelineLayoutCreateInfo.pPushConstantRanges = finalPushConstantRangeData.data();
        }

        VkResult pipelineLayoutResult =
            vkCreatePipelineLayout(GetDevice()->GetVulkanDevice(),
                                   &pipelineLayoutCreateInfo, nullptr, &vulkanPipelineLayout);

        if (pipelineLayoutResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkPipelineLayout.",
                                                             pipelineLayoutResult);
        }

        return vulkanPipelineLayout;
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorPool()
    {
        if (_vulkanDescriptorPool.HasValue())
        {
            vkDestroyDescriptorPool(GetDevice()->GetVulkanDevice(),
                                    _vulkanDescriptorPool.Get(), nullptr);
            _vulkanDescriptorPool.Reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorSets(
        NovelRT::Utilities::Span<VkDescriptorSet> vulkanDescriptorSets)
    {
        vkFreeDescriptorSets(GetDevice()->GetVulkanDevice(),
                             _vulkanDescriptorPool.Get(), static_cast<int32_t>(vulkanDescriptorSets.size()),
                             vulkanDescriptorSets.data());
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorSetLayout()
    {
        if (_vulkanDescriptorSetLayout.HasValue())
        {
            vkDestroyDescriptorSetLayout(GetDevice()->GetVulkanDevice(), _vulkanDescriptorSetLayout.Get(), nullptr);
            _vulkanDescriptorSetLayout.Reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyPipelineLayout()
    {
        if (_vulkanPipelineLayout.HasValue())
        {
            vkDestroyPipelineLayout(GetDevice()->GetVulkanDevice(),
                                    _vulkanPipelineLayout.Get(), nullptr);
            _vulkanPipelineLayout.Reset();
        }
    }

    VulkanGraphicsPipelineSignature::VulkanGraphicsPipelineSignature(
        VulkanGraphicsDevice* device,
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
        NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept
        : _device(device)
        , _srcBlendFactor(srcBlendFactor)
        , _dstBlendFactor(dstBlendFactor)
        , _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end()))
        , _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end()))
        , _pushConstantRanges(std::vector<GraphicsPushConstantRange>(pushConstantRanges.begin(), pushConstantRanges.end()))
        , _vulkanDescriptorPool([&]() { return CreateDescriptorPool(); })
        , _vulkanDescriptorSetLayout([&]() { return CreateDescriptorSetLayout(); })
        , _vulkanPipelineLayout([&]() { return CreatePipelineLayout(); })
    {
    }

    VulkanGraphicsPipelineSignature::~VulkanGraphicsPipelineSignature()
    {
        DestroyDescriptorSetLayout();
        DestroyDescriptorPool();
        DestroyPipelineLayout();
    }
}

template class NovelRT::Graphics::GraphicsPipelineSignature<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
