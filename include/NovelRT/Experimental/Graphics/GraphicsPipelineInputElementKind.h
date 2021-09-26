// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENTKIND_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENTKIND_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    enum class GraphicsPipelineInputElementKind : uint32_t
    {
        Unknown = 0,
        Position = 1,
        Colour = 2,
        Normal = 3,
        TextureCoordinate = 4
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENTKIND_H
