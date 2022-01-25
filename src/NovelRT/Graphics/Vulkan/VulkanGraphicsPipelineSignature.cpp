// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{
    VkDescriptorPool VulkanGraphicsPipelineSignature::CreateDescriptorPool()
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
                vkCreateDescriptorPool(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                       &descriptorPoolCreateInfo, nullptr, &returnDescriptorPool);

            if (descriptorPoolResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorPool.",
                                                                 descriptorPoolResult);
            }
        }

        return returnDescriptorPool;
    }

    VkDescriptorSet VulkanGraphicsPipelineSignature::CreateDescriptorSet()
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
                vkAllocateDescriptorSets(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                         &descriptorSetAllocateInfo, &returnDescriptorSet);

            if (allocatorDescriptorSetsResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorSet.",
                                                                 allocatorDescriptorSetsResult);
            }
        }

        return returnDescriptorSet;
    }

    VkDescriptorSetLayout VulkanGraphicsPipelineSignature::CreateDescriptorSetLayout()
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
                        auto stageFlags = GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

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
                        auto stageFlags = GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

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

            VkResult descriptorSetLayoutResult = vkCreateDescriptorSetLayout(
                std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                &descriptorSetLayoutCreateInfo, nullptr, &vulkanDescriptorSetLayout);

            if (descriptorSetLayoutResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException("Failed to create the VkDescriptorSetLayout.",
                                                                 descriptorSetLayoutResult);
            }
        }

        return vulkanDescriptorSetLayout;
    }

    VkPipelineLayout VulkanGraphicsPipelineSignature::CreatePipelineLayout()
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

        VkResult pipelineLayoutResult =
            vkCreatePipelineLayout(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
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
        if (_vulkanDescriptorPool.isCreated())
        {
            vkDestroyDescriptorPool(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                    _vulkanDescriptorPool.getActual(), nullptr);
            _vulkanDescriptorPool.reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorSets(gsl::span<VkDescriptorSet> vulkanDescriptorSets)
    {
        vkFreeDescriptorSets(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                             _vulkanDescriptorPool.getActual(), static_cast<int32_t>(vulkanDescriptorSets.size()),
                             vulkanDescriptorSets.data());
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorSetLayout()
    {
        if (_vulkanDescriptorSetLayout.isCreated())
        {
            vkDestroyDescriptorSetLayout(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                         _vulkanDescriptorSetLayout.getActual(), nullptr);
            _vulkanDescriptorSetLayout.reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyPipelineLayout()
    {
        if (_vulkanPipelineLayout.isCreated())
        {
            vkDestroyPipelineLayout(std::static_pointer_cast<VulkanGraphicsDevice>(GetDevice())->GetVulkanDevice(),
                                    _vulkanPipelineLayout.getActual(), nullptr);
            _vulkanPipelineLayout.reset();
        }
    }

    VulkanGraphicsPipelineSignature::VulkanGraphicsPipelineSignature(
        std::shared_ptr<VulkanGraphicsDevice> device,
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        gsl::span<const GraphicsPipelineInput> inputs,
        gsl::span<const GraphicsPipelineResource> resources) noexcept
        : GraphicsPipelineSignature(std::move(device), srcBlendFactor, dstBlendFactor, inputs, resources),
          _vulkanDescriptorPool([&]() { return CreateDescriptorPool(); }),
          _vulkanDescriptorSetLayout([&]() { return CreateDescriptorSetLayout(); }),
          _vulkanPipelineLayout([&]() { return CreatePipelineLayout(); })
    {
    }

    VkShaderStageFlags VulkanGraphicsPipelineSignature::GetVulkanShaderStageFlags(
        ShaderProgramVisibility shaderVisibility) const noexcept
    {
        VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL;

        if (shaderVisibility != ShaderProgramVisibility::All)
        {
            if ((shaderVisibility & ShaderProgramVisibility::Vertex) == ShaderProgramVisibility::NoneOrUnknown)
            {
                stageFlags &= ~VK_SHADER_STAGE_VERTEX_BIT;
            }
            if ((shaderVisibility & ShaderProgramVisibility::Pixel) == ShaderProgramVisibility::NoneOrUnknown)
            {
                stageFlags &= ~VK_SHADER_STAGE_FRAGMENT_BIT;
            }
        }

        return stageFlags;
    }

    VulkanGraphicsPipelineSignature::~VulkanGraphicsPipelineSignature()
    {
        DestroyDescriptorSetLayout();
        DestroyDescriptorPool();
        DestroyPipelineLayout();
    }
}
