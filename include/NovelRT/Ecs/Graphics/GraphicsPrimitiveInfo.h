// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSPRIMITIVEINFO_H
#define NOVELRT_GRAPHICSPRIMITIVEINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct GraphicsPrimitiveInfo
    {
        std::shared_ptr<Experimental::Graphics::GraphicsPrimitive> primitive = nullptr;
        Atom ecsVertexDataId = 0;
        Atom ecsTextureId = 0;
        Atom ecsPipelineId = 0;
    };
}

#endif // NOVELRT_GRAPHICSPRIMITIVEINFO_H
