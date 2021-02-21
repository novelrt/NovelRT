// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H

#include "GraphicsResource.h"

namespace NovelRT::Experimental::Graphics
{
    class GraphicsBuffer : public GraphicsResource
    {
    public:
        explicit GraphicsBuffer(GraphicsResourceCpuAccessKind enabledAccessMode) noexcept
            : GraphicsResource(enabledAccessMode)
        {
        }


    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H
