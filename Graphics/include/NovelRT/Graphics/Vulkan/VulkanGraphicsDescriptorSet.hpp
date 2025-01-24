#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsPipeline;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;

    class VulkanGraphicsDescriptorSet final : public VulkanGraphicsResource
    {
    private:
        std::shared_ptr<VulkanGraphicsPipeline> _pipeline;

    public:
        explicit VulkanGraphicsDescriptorSet(std::shared_ptr<VulkanGraphicsPipeline> targetPipeline) noexcept;

        ~VulkanGraphicsDescriptorSet() = default;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsPipeline> GetPipeline() const noexcept;

        void AddBuffers(NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsBuffer>> buffers);
        
        void AddTextures(NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsTexture>> textures);
    };
}