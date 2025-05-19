#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <typeindex>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline
    {
    private:
        VulkanGraphicsDevice* _device;
        VulkanShaderProgram* _vertexShader;
        VulkanShaderProgram* _pixelShader;
        VulkanGraphicsPipelineSignature* _signature;

        mutable NovelRT::Utilities::Lazy<VkPipeline> _vulkanPipeline;
        [[nodiscard]] VkPipeline CreateVulkanPipeline(bool imguiRenderMode);
        [[nodiscard]] size_t GetInputElementsCount(
            NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs) const noexcept;
        [[nodiscard]] VkFormat GetInputElementFormat(std::type_index type) const noexcept;

    public:
        VulkanGraphicsPipeline(VulkanGraphicsDevice* device,
                               VulkanGraphicsPipelineSignature* signature,
                               VulkanShaderProgram* vertexShader,
                               VulkanShaderProgram* pixelShader,
                               bool imguiRenderMode) noexcept;

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] VulkanShaderProgram* GetPixelShader() const noexcept
        {
            return _pixelShader;
        }

        [[nodiscard]] VulkanShaderProgram* GetVertexShader() const noexcept
        {
            return _vertexShader;
        }

        [[nodiscard]] VulkanGraphicsPipelineSignature* GetSignature() const noexcept
        {
            return _signature;
        }

        [[nodiscard]] VkPipeline GetVulkanPipeline() const
        {
            return _vulkanPipeline.Get();
        }

        [[nodiscard]] bool HasVertexShader() const noexcept
        {
            return _vertexShader != nullptr;
        }

        [[nodiscard]] bool HasPixelShader() const noexcept
        {
            return _pixelShader != nullptr;
        }

        [[nodiscard]] std::unique_ptr<VulkanGraphicsDescriptorSet> CreateDescriptorSet();
    };
}
