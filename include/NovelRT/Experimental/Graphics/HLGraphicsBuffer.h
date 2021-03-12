// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_HLGRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_HLGRAPHICSBUFFER_H

#include "HLGraphicsResource.h"

namespace NovelRT::Experimental::Graphics
{
    class HLGraphicsBuffer : public HLGraphicsResource
    {
    public:
        explicit HLGraphicsBuffer(GraphicsResourceCpuAccessKind enabledAccessMode) noexcept
            : HLGraphicsResource(enabledAccessMode)
        {
        }


    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_HLGRAPHICSBUFFER_H
