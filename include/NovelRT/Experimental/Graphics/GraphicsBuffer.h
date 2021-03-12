// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H

#include "HLGraphicsResource.h"

namespace NovelRT::Experimental::Graphics
{
    class GraphicsBuffer : public HLGraphicsResource
    {
    public:
        explicit GraphicsBuffer(GraphicsResourceCpuAccessKind enabledAccessMode) noexcept
            : HLGraphicsResource(enabledAccessMode)
        {
        }


    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSBUFFER_H
