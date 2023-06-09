// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSPIPELINESIGNATURE_H
#define NOVELRT_GRAPHICS_GRAPHICSPIPELINESIGNATURE_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsPipelineSignature : public GraphicsDeviceObject
    {
    private:
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;

    public:
        GraphicsPipelineSignature(std::shared_ptr<GraphicsDevice> device,
                                  GraphicsPipelineBlendFactor srcBlendFactor,
                                  GraphicsPipelineBlendFactor dstBlendFactor,
                                  NovelRT::Core::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
                                  NovelRT::Core::Utilities::Misc::Span<const GraphicsPipelineResource> resources) noexcept;

        [[nodiscard]] NovelRT::Core::Utilities::Misc::Span<const GraphicsPipelineInput> GetInputs() const noexcept;
        [[nodiscard]] NovelRT::Core::Utilities::Misc::Span<const GraphicsPipelineResource> GetResources() const noexcept;

        [[nodiscard]] inline GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept
        {
            return _srcBlendFactor;
        }

        [[nodiscard]] inline GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept
        {
            return _dstBlendFactor;
        }
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSPIPELINESIGNATURE_H
