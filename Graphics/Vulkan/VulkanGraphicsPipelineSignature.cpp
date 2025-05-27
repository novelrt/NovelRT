// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp>

#include <NovelRT/Utilities/Operators.hpp>

#include <algorithm>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipelineSignature = GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>;
    using VulkanShaderProgram = ShaderProgram<Vulkan::VulkanGraphicsBackend>;

    VkDescriptorPool CreateDescriptorPool(VulkanGraphicsPipelineSignature* signature)
    {
        auto resources = signature->GetResources();
        if (resources.size() == 0)
            return VK_NULL_HANDLE;

        auto constantBuffers = std::count_if(resources.begin(), resources.end(), [](const auto& resource) { return resource.GetKind() == GraphicsPipelineResourceKind::ConstantBuffer; });
        auto textures = std::count_if(resources.begin(), resources.end(), [](const auto& resource) { return resource.GetKind() == GraphicsPipelineResourceKind::Texture; });

        std::vector<VkDescriptorPoolSize> vulkanDescriptorPoolSizes{};


        if (constantBuffers > 0)
        {
            VkDescriptorPoolSize value{};
            value.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            value.descriptorCount = static_cast<uint32_t>(constantBuffers);
            vulkanDescriptorPoolSizes.push_back(value);
        }

        if (textures > 0)
        {
            VkDescriptorPoolSize value{};
            value.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            value.descriptorCount = static_cast<uint32_t>(textures);
            vulkanDescriptorPoolSizes.push_back(value);
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

        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        descriptorPoolCreateInfo.maxSets = 100;

        // TODO: These need to be multiplied by 100 I think. Oh no.
        descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(vulkanDescriptorPoolSizes.size());
        descriptorPoolCreateInfo.pPoolSizes = vulkanDescriptorPoolSizes.data();

        auto device = signature->GetDevice().lock();
        VkDescriptorPool returnDescriptorPool = VK_NULL_HANDLE;
        VkResult descriptorPoolResult = vkCreateDescriptorPool(device->GetVulkanDevice(), &descriptorPoolCreateInfo, nullptr, &returnDescriptorPool);

        if (descriptorPoolResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorPool.",
                                                                descriptorPoolResult);
        }

        return returnDescriptorPool;
    }

    VkDescriptorSetLayout CreateDescriptorSetLayout(VulkanGraphicsPipelineSignature* signature)
    {
        auto resources = signature->GetResources();
        if (resources.size() == 0)
            return VK_NULL_HANDLE;

        std::vector<VkDescriptorSetLayoutBinding> descriptorSetLayoutBindings(resources.size());
        uint32_t bindingIndex = 0;

        for (auto&& resource : resources)
        {
            switch (resource.GetKind())
            {
                case GraphicsPipelineResourceKind::ConstantBuffer:
                {
                    auto stageFlags = Vulkan::Utilities::GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

                    VkDescriptorSetLayoutBinding value{};
                    value.binding = bindingIndex++;
                    value.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    value.descriptorCount = 1;
                    value.stageFlags = stageFlags;
                    descriptorSetLayoutBindings.push_back(value);
                    break;
                }
                case GraphicsPipelineResourceKind::Texture:
                {
                    auto stageFlags = Vulkan::Utilities::GetVulkanShaderStageFlags(resource.GetShaderProgramVisibility());

                    VkDescriptorSetLayoutBinding value{};
                    value.binding = bindingIndex++;
                    value.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    value.descriptorCount = 1;
                    value.stageFlags = stageFlags;
                    descriptorSetLayoutBindings.push_back(value);
                    break;
                }
                case GraphicsPipelineResourceKind::Unknown:
                default:
                {
                    break;
                }
            }
        }

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayoutBindings.size());
        descriptorSetLayoutCreateInfo.pBindings = descriptorSetLayoutBindings.data();

        auto device = signature->GetDevice().lock();
        VkDescriptorSetLayout vulkanDescriptorSetLayout = VK_NULL_HANDLE;
        VkResult descriptorSetLayoutResult = vkCreateDescriptorSetLayout(device->GetVulkanDevice(), &descriptorSetLayoutCreateInfo, nullptr, &vulkanDescriptorSetLayout);

        if (descriptorSetLayoutResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkDescriptorSetLayout.",
                                                                descriptorSetLayoutResult);
        }

        return vulkanDescriptorSetLayout;
    }

    VkPipelineLayout CreatePipelineLayout(VulkanGraphicsPipelineSignature* signature)
    {
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        VkDescriptorSetLayout descriptorSetLayout = signature->GetVulkanDescriptorSetLayout();

        if (descriptorSetLayout != VK_NULL_HANDLE)
        {
            pipelineLayoutCreateInfo.setLayoutCount = 1;
            pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
        }

        auto pushConstantRanges = signature->GetPushConstantRanges();
        if (pushConstantRanges.size() != 0)
        {
            std::vector<VkPushConstantRange> finalPushConstantRangeData(pushConstantRanges.size());
            std::transform(
                pushConstantRanges.begin(), pushConstantRanges.end(),
                finalPushConstantRangeData.begin(),
                [&](const GraphicsPushConstantRange& rangeData) {
                    VkPushConstantRange returnData{};
                    returnData.stageFlags = Vulkan::Utilities::GetVulkanShaderStageFlags(rangeData.visibilityFlags);
                    returnData.size = static_cast<uint32_t>(rangeData.size);
                    returnData.offset = static_cast<uint32_t>(rangeData.offset);

                    return returnData;
                });

            pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(finalPushConstantRangeData.size());
            pipelineLayoutCreateInfo.pPushConstantRanges = finalPushConstantRangeData.data();
        }

        auto device = signature->GetDevice().lock();
        VkPipelineLayout vulkanPipelineLayout = VK_NULL_HANDLE;
        VkResult pipelineLayoutResult = vkCreatePipelineLayout(device->GetVulkanDevice(), &pipelineLayoutCreateInfo, nullptr, &vulkanPipelineLayout);

        if (pipelineLayoutResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkPipelineLayout.",
                                                             pipelineLayoutResult);
        }

        return vulkanPipelineLayout;
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsPipelineSignature> VulkanGraphicsPipelineSignature::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsPipelineSignature>(GraphicsDeviceObject::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsPipelineSignature> VulkanGraphicsPipelineSignature::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsPipelineSignature>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsPipelineSignature::GraphicsPipelineSignature(
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
        NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept
        : _device(std::move(device))
        , _srcBlendFactor(srcBlendFactor)
        , _dstBlendFactor(dstBlendFactor)
        , _inputs(inputs.begin(), inputs.end())
        , _resources(resources.begin(), resources.end())
        , _pushConstantRanges(std::vector<GraphicsPushConstantRange>(pushConstantRanges.begin(), pushConstantRanges.end()))
        , _vulkanDescriptorPool([this]() { return CreateDescriptorPool(this); })
        , _vulkanDescriptorSetLayout([this]() { return CreateDescriptorSetLayout(this); })
        , _vulkanPipelineLayout([this]() { return CreatePipelineLayout(this); })
    {
    }

    VulkanGraphicsPipelineSignature::~GraphicsPipelineSignature()
    {
        DestroyDescriptorSetLayout();
        DestroyDescriptorPool();
        DestroyPipelineLayout();
    }

    [[nodiscard]] std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsPipelineSignature::GetDevice() const
    {
        return _device;
    }

    [[nodiscard]] GraphicsPipelineBlendFactor VulkanGraphicsPipelineSignature::GetSrcBlendFactor() const noexcept
    {
        return _srcBlendFactor;
    }

    [[nodiscard]] GraphicsPipelineBlendFactor VulkanGraphicsPipelineSignature::GetDstBlendFactor() const noexcept
    {
        return _dstBlendFactor;
    }

    [[nodiscard]] std::shared_ptr<VulkanGraphicsDescriptorSet> VulkanGraphicsPipelineSignature::CreateDescriptorSet(const std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>>& pipeline)
    {
        VkDescriptorPool vulkanDescriptorPool = GetVulkanDescriptorPool();
        if (vulkanDescriptorPool == VK_NULL_HANDLE)
        {
            return nullptr;
        }

        VkDescriptorSetLayout vulkanDescriptorSetLayout = GetVulkanDescriptorSetLayout();

        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
        descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocateInfo.descriptorPool = vulkanDescriptorPool;
        descriptorSetAllocateInfo.descriptorSetCount = 1;
        descriptorSetAllocateInfo.pSetLayouts = &vulkanDescriptorSetLayout;

        auto device = _device.lock();
        VkDescriptorSet returnDescriptorSet = VK_NULL_HANDLE;
        VkResult allocatorDescriptorSetsResult = vkAllocateDescriptorSets(device->GetVulkanDevice(), &descriptorSetAllocateInfo, &returnDescriptorSet);

        if (allocatorDescriptorSetsResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create VkDescriptorSet.",
                                                                allocatorDescriptorSetsResult);
        }

        return std::make_shared<VulkanGraphicsDescriptorSet>(pipeline, returnDescriptorSet);
    }

    [[nodiscard]] std::vector<GraphicsPipelineInput> VulkanGraphicsPipelineSignature::GetInputs() const noexcept
    {
        return _inputs;
    }

    [[nodiscard]] std::vector<GraphicsPipelineResource> VulkanGraphicsPipelineSignature::GetResources() const noexcept
    {
        return _resources;
    }

    [[nodiscard]] std::vector<GraphicsPushConstantRange> VulkanGraphicsPipelineSignature::GetPushConstantRanges() const noexcept
    {
        return _pushConstantRanges;
    }

    [[nodiscard]] VkDescriptorPool VulkanGraphicsPipelineSignature::GetVulkanDescriptorPool() const
    {
        return _vulkanDescriptorPool.Get();
    }

    [[nodiscard]] VkDescriptorSetLayout VulkanGraphicsPipelineSignature::GetVulkanDescriptorSetLayout() const
    {
        return _vulkanDescriptorSetLayout.Get();
    }

    [[nodiscard]] VkPipelineLayout VulkanGraphicsPipelineSignature::GetVulkanPipelineLayout() const
    {
        return _vulkanPipelineLayout.Get();
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorPool()
    {
        if (_vulkanDescriptorPool.HasValue())
        {
            auto device = _device.lock();
            vkDestroyDescriptorPool(device->GetVulkanDevice(), _vulkanDescriptorPool.Get(), nullptr);
            _vulkanDescriptorPool.Reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyDescriptorSetLayout()
    {
        if (_vulkanDescriptorSetLayout.HasValue())
        {
            auto device = _device.lock();
            vkDestroyDescriptorSetLayout(device->GetVulkanDevice(), _vulkanDescriptorSetLayout.Get(), nullptr);
            _vulkanDescriptorSetLayout.Reset();
        }
    }

    void VulkanGraphicsPipelineSignature::DestroyPipelineLayout()
    {
        if (_vulkanPipelineLayout.HasValue())
        {
            auto device = _device.lock();
            vkDestroyPipelineLayout(device->GetVulkanDevice(), _vulkanPipelineLayout.Get(), nullptr);
            _vulkanPipelineLayout.Reset();
        }
    }
}
