// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{

    GraphicsPipelineResourceKind Graphics::GraphicsPipelineResource::GetKind() const noexcept
    {
        return _kind;
    }

    ShaderProgramVisibility GraphicsPipelineResource::GetShaderProgramVisibility() const noexcept
    {
        return _visibility;
    }
} // namespace NovelRT::Experimental::Graphics
