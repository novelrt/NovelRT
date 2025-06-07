#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsDescriptorSet;

    template<typename TBackend>
    struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsPipelineSignature : public GraphicsDeviceObject<TBackend>
    {
    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> shared_from_this();

        GraphicsPipelineSignature() = delete;
        virtual ~GraphicsPipelineSignature() noexcept override = default;

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept;
        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<TBackend>> CreateDescriptorSet(
            std::shared_ptr<GraphicsPipeline<TBackend>> pipeline);

        [[nodiscard]] NovelRT::Utilities::Span<const GraphicsPipelineInput> GetInputs() const noexcept;
        [[nodiscard]] NovelRT::Utilities::Span<const GraphicsPipelineResource> GetResources() const noexcept;
    };
}
