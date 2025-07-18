// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>

#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Maths/GeoVector4F.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipelineSignature = GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>;
    using VulkanShaderProgram = ShaderProgram<Vulkan::VulkanGraphicsBackend>;

    size_t GetInputElementsCount(NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs)
    {
        size_t returnCount = 0;

        for (auto&& input : inputs)
        {
            returnCount += input.GetElements().size();
        }

        return returnCount;
    }

    VkFormat GetInputElementFormat(std::type_index type, GraphicsPipelineInputElementKind kind)
    {
        VkFormat returnFormat = VK_FORMAT_UNDEFINED;

        if (type == typeid(Maths::GeoVector2F))
        {
            returnFormat = VK_FORMAT_R32G32_SFLOAT;
        }
        else if (type == typeid(Maths::GeoVector3F))
        {
            returnFormat = VK_FORMAT_R32G32B32_SFLOAT;
        }
        else if (type == typeid(Maths::GeoVector4F))
        {
            returnFormat = VK_FORMAT_R32G32B32A32_SFLOAT;
        }
        else if(kind == GraphicsPipelineInputElementKind::Colour)
        {
            if (type == typeid(uint32_t))
            {
                returnFormat = VK_FORMAT_R8G8B8A8_UNORM;
            }
        }

        return returnFormat;
    }

    VkPipeline CreateVulkanPipeline(VulkanGraphicsPipeline* pipeline, bool imguiRenderMode)
    {
        std::array<VkPipelineShaderStageCreateInfo, 2> pipelineShaderStageCreateInfos{};
        uint32_t pipelineShaderStageCreateInfosCount = 0;

        VkVertexInputBindingDescription vertexInputBindingDescription{};
        vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions{};

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
        pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
        pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;

        VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{};
        pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        pipelineInputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo{};
        pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        pipelineViewportStateCreateInfo.viewportCount = 1;
        pipelineViewportStateCreateInfo.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{};
        pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        pipelineRasterizationStateCreateInfo.frontFace = imguiRenderMode ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
        pipelineRasterizationStateCreateInfo.cullMode = imguiRenderMode ? VK_CULL_MODE_NONE : VK_CULL_MODE_BACK_BIT;
        pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
        if(imguiRenderMode)
        {
            pipelineRasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
        }

        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{};
        pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkStencilOpState frontState{};
        frontState.compareOp = VK_COMPARE_OP_ALWAYS;

        VkStencilOpState backState{};
        backState.compareOp = VK_COMPARE_OP_ALWAYS;

        VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo{};
        pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        pipelineDepthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_ALWAYS;
        pipelineDepthStencilStateCreateInfo.front = frontState;
        pipelineDepthStencilStateCreateInfo.back = backState;

        auto signature = pipeline->GetSignature();
        VkBlendFactor srcBlendFactor = Vulkan::Utilities::GetVulkanBlendFactor(signature->GetSrcBlendFactor());
        VkBlendFactor dstBlendFactor = Vulkan::Utilities::GetVulkanBlendFactor(signature->GetDstBlendFactor());

        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState{};
        pipelineColorBlendAttachmentState.blendEnable = true;
        pipelineColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        pipelineColorBlendAttachmentState.srcColorBlendFactor = srcBlendFactor;
        pipelineColorBlendAttachmentState.srcAlphaBlendFactor = srcBlendFactor;
        pipelineColorBlendAttachmentState.dstColorBlendFactor = dstBlendFactor;
        pipelineColorBlendAttachmentState.srcAlphaBlendFactor = dstBlendFactor;
        // pipelineColorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_SUBTRACT;

        VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo{};
        pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        pipelineColorBlendStateCreateInfo.attachmentCount = 1;
        pipelineColorBlendStateCreateInfo.pAttachments = &pipelineColorBlendAttachmentState;

        std::array<VkDynamicState, 2> dynamicStates{VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

        VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
        pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        pipelineDynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        pipelineDynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

        auto device = pipeline->GetDevice();
        VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
        pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineCreateInfo.pViewportState = &pipelineViewportStateCreateInfo;
        pipelineCreateInfo.pRasterizationState = &pipelineRasterizationStateCreateInfo;
        pipelineCreateInfo.pMultisampleState = &pipelineMultisampleStateCreateInfo;
        pipelineCreateInfo.pDepthStencilState = &pipelineDepthStencilStateCreateInfo;
        pipelineCreateInfo.pColorBlendState = &pipelineColorBlendStateCreateInfo;
        pipelineCreateInfo.pDynamicState = &pipelineDynamicStateCreateInfo;
        pipelineCreateInfo.layout = signature->GetVulkanPipelineLayout();
        pipelineCreateInfo.renderPass = device->GetVulkanRenderPass();

        if (pipeline->HasVertexShader())
        {
            auto vertexShader = pipeline->GetVertexShader();
            const uint32_t shaderIndex = pipelineShaderStageCreateInfosCount++;

            VkPipelineShaderStageCreateInfo vertexShaderStageCreateInfo{};
            vertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            vertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
            vertexShaderStageCreateInfo.module = vertexShader->GetShaderModule();
            vertexShaderStageCreateInfo.pName = vertexShader->GetEntryPointName().c_str();

            pipelineShaderStageCreateInfos[shaderIndex] = vertexShaderStageCreateInfo;

            auto inputs = signature->GetInputs();
            size_t inputsLength = inputs.size();

            size_t inputElementsCount = GetInputElementsCount(inputs);
            size_t inputElementsIndex = 0;

            if (inputElementsCount != 0)
            {
                vertexInputAttributeDescriptions.resize(inputElementsCount);

                for (size_t inputIndex = 0; inputIndex < inputsLength; inputIndex++)
                {
                    auto& input = inputs[inputIndex];
                    auto inputElements = input.GetElements();
                    size_t inputElementsLength = inputElements.size();
                    uint32_t inputBindingStride = 0;

                    for (size_t inputElementIndex = 0; inputElementIndex < inputElementsLength; inputElementIndex++)
                    {
                        auto inputElement = inputElements[inputElementIndex];

                        VkVertexInputAttributeDescription insertValue{};
                        insertValue.location = static_cast<uint32_t>(inputElementIndex);
                        insertValue.binding = static_cast<uint32_t>(inputIndex);
                        insertValue.format = GetInputElementFormat(inputElement.GetType(), inputElement.GetKind());
                        insertValue.offset = inputBindingStride;

                        vertexInputAttributeDescriptions[inputElementsIndex] = insertValue;

                        inputBindingStride += static_cast<uint32_t>(inputElement.GetSize());
                        inputElementsIndex++;
                    }

                    vertexInputBindingDescription.stride = inputBindingStride;
                }
            }

            pipelineCreateInfo.pVertexInputState = &pipelineVertexInputStateCreateInfo;
            pipelineCreateInfo.pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo;
        }

        if (pipeline->HasPixelShader())
        {
            auto pixelShader = pipeline->GetPixelShader();
            const uint32_t shaderIndex = pipelineShaderStageCreateInfosCount++;

            VkPipelineShaderStageCreateInfo pixelShaderStageCreateInfo{};
            pixelShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            pixelShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            pixelShaderStageCreateInfo.module = pixelShader->GetShaderModule();
            pixelShaderStageCreateInfo.pName = pixelShader->GetEntryPointName().c_str();

            pipelineShaderStageCreateInfos[shaderIndex] = pixelShaderStageCreateInfo;
        }

        if (pipelineShaderStageCreateInfosCount != 0)
        {
            pipelineCreateInfo.stageCount = pipelineShaderStageCreateInfosCount;
            pipelineCreateInfo.pStages = pipelineShaderStageCreateInfos.data();
        }

        pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount =
            static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
        pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

        VkPipeline vulkanPipeline = VK_NULL_HANDLE;
        VkResult createGraphicsPipelineResult = vkCreateGraphicsPipelines(device->GetVulkanDevice(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &vulkanPipeline);

        if (createGraphicsPipelineResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create a VulkanGraphicsPipeline.",
                                                             createGraphicsPipelineResult);
        }

        return vulkanPipeline;
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsPipeline> VulkanGraphicsPipeline::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsPipeline>(GraphicsDeviceObject::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsPipeline> VulkanGraphicsPipeline::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsPipeline>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsPipeline::GraphicsPipeline(
        std::shared_ptr<VulkanGraphicsDevice> device,
        std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
        //NOLINTBEGIN(bugprone-easily-swappable-parameters) - no sane way to handle this
        std::shared_ptr<VulkanShaderProgram> vertexShader,
        std::shared_ptr<VulkanShaderProgram> pixelShader,
        bool imguiRenderMode) noexcept
        //NOLINTEND(bugprone-easily-swappable-parameters)
        : _device(std::move(device))
        , _vertexShader(std::move(vertexShader))
        , _pixelShader(std::move(pixelShader))
        , _signature(std::move(signature))
        , _vulkanPipeline([this, imguiRenderMode]() { return CreateVulkanPipeline(this, imguiRenderMode); })
    { }

    [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsPipeline::GetDevice() const
    {
        return _device;
    }

    bool VulkanGraphicsPipeline::HasVertexShader() const noexcept
    {
        return _vertexShader != nullptr;
    }

    bool VulkanGraphicsPipeline::HasPixelShader() const noexcept
    {
        return _pixelShader != nullptr;
    }

    std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsPipeline::GetVertexShader() const noexcept
    {
        return _vertexShader;
    }

    std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsPipeline::GetPixelShader() const noexcept
    {
        return _pixelShader;
    }

    std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsPipeline::GetSignature() const noexcept
    {
        return _signature;
    }

    std::shared_ptr<VulkanGraphicsDescriptorSet> VulkanGraphicsPipeline::CreateDescriptorSet()
    {
        return _signature->CreateDescriptorSet(shared_from_this());
    }

    VkPipeline VulkanGraphicsPipeline::GetVulkanPipeline() const
    {
        return _vulkanPipeline.Get();
    }
}
