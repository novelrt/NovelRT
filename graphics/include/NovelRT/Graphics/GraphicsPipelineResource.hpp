#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>

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
