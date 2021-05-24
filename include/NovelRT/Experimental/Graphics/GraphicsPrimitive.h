// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSPRIMITIVE_H
#define NOVELRT_GRAPHICSPRIMITIVE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsPrimitive
    {
    private:
        std::shared_ptr<GraphicsPipeline> _pipeline;
        
    };
}

#endif // NOVELRT_GRAPHICSPRIMITIVE_H
