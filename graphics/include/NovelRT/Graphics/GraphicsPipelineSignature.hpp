#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>

namespace NovelRT::Graphics
{
    class GraphicsPipelineSignature : public GraphicsDeviceObject
    {
        class GraphicsDescriptorSet;

    private:
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;

    public:
        GraphicsPipelineSignature(std::shared_ptr<GraphicsDevice> device,
                                  GraphicsPipelineBlendFactor srcBlendFactor,
                                  GraphicsPipelineBlendFactor dstBlendFactor,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> resources) noexcept;

        virtual ~GraphicsPipelineSignature() = default;
        
        [[nodiscard]] NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> GetInputs() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> GetResources() const noexcept;

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept;

        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept;

        [[nodiscard]] virtual std::shared_ptr<GraphicsDescriptorSet> CreateDescriptorSet() = 0;
    };
}
