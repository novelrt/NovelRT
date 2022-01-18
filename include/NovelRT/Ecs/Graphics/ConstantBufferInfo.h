// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CONSTANTBUFFERINFO_H
#define NOVELRT_CONSTANTBUFFERINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct ConstantBufferInfo
    {
        Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource> gpuConstantBufferRegion =
            {};
    };
}

#endif // NOVELRT_CONSTANTBUFFERINFO_H
