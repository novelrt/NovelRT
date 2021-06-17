// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINERESOURCEKIND_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINERESOURCEKIND_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    enum class GraphicsPipelineResourceKind : uint32_t
    {
        Unknown = 0,
        ConstantBuffer = 1,
        Texture = 2
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINERESOURCEKIND_H
