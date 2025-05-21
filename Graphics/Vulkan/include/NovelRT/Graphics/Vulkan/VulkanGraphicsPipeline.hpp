#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <NovelRT/Graphics/GraphicsPipeline.hpp>

#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsPipeline<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> _vertexShader;
        std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> _pixelShader;
        std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> _signature;

        mutable NovelRT::Utilities::Lazy<VkPipeline> _vulkanPipeline;
        [[nodiscard]] VkPipeline CreateVulkanPipeline(bool imguiRenderMode);
        [[nodiscard]] size_t GetInputElementsCount(
            NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs) const noexcept;

    public:
        GraphicsPipeline(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                               std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> signature,
                               std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> vertexShader,
                               std::shared_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> pixelShader,
                               bool imguiRenderMode) noexcept;
        virtual ~GraphicsPipeline() override = default;

        [[nodiscard]] std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const noexcept;

        [[nodiscard]] bool HasVertexShader() const noexcept;
        [[nodiscard]] bool HasPixelShader() const noexcept;

        [[nodiscard]] std::weak_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> GetPixelShader() const noexcept;
        [[nodiscard]] std::weak_ptr<ShaderProgram<Vulkan::VulkanGraphicsBackend>> GetVertexShader() const noexcept;

        [[nodiscard]] std::weak_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>> GetSignature() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>> CreateDescriptorSet();

        [[nodiscard]] VkPipeline GetVulkanPipeline() const;
    };
}
