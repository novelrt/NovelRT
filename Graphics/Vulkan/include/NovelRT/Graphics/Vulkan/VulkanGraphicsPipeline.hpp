#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <typeindex>
#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline : public std::enable_shared_from_this<VulkanGraphicsPipeline>
    {
    private:
        std::shared_ptr<VulkanGraphicsDevice> _device;
        std::shared_ptr<VulkanShaderProgram> _vertexShader;
        std::shared_ptr<VulkanShaderProgram> _pixelShader;
        std::shared_ptr<VulkanGraphicsPipelineSignature> _signature;

        NovelRT::Utilities::Lazy<VkPipeline> _vulkanPipeline;
        [[nodiscard]] VkPipeline CreateVulkanPipeline();
        [[nodiscard]] size_t GetInputElementsCount(
            NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs) const noexcept;
        [[nodiscard]] VkFormat GetInputElementFormat(std::type_index index) const noexcept;

    public:
        VulkanGraphicsPipeline(std::shared_ptr<VulkanGraphicsDevice> device,
                               std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
                               std::shared_ptr<VulkanShaderProgram> vertexShader,
                               std::shared_ptr<VulkanShaderProgram> pixelShader) noexcept;

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanShaderProgram> GetPixelShader() const noexcept
        {
            return _vertexShader;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanShaderProgram> GetVertexShader() const noexcept
        {
            return _pixelShader;
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsPipelineSignature> GetSignature() const noexcept
        {
            return _signature;
        }

        [[nodiscard]] inline VkPipeline GetVulkanPipeline()
        {
            return _vulkanPipeline.getActual();
        }
        
        [[nodiscard]] bool HasVertexShader() const noexcept
        {
            return _vertexShader != nullptr;
        }

        [[nodiscard]] bool HasPixelShader() const noexcept
        {
            return _pixelShader != nullptr;
        }

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDescriptorSet> CreateDescriptorSet();
    };
}
