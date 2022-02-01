// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSPIPELINERESOURCE_H
#define NOVELRT_GRAPHICS_GRAPHICSPIPELINERESOURCE_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsPipelineResource
    {
    private:
        GraphicsPipelineResourceKind _kind;
        ShaderProgramVisibility _visibility;

    public:
        GraphicsPipelineResource(GraphicsPipelineResourceKind kind, ShaderProgramVisibility visibility) noexcept
            : _kind(kind), _visibility(visibility)
        {
        }

        [[nodiscard]] GraphicsPipelineResourceKind GetKind() const noexcept;
        [[nodiscard]] ShaderProgramVisibility GetShaderProgramVisibility() const noexcept;
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSPIPELINERESOURCE_H
