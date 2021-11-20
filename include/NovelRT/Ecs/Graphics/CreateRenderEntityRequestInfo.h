// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CREATERENDERENTITYREQUESTINFO_H
#define NOVELRT_CREATERENDERENTITYREQUESTINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct CreateRenderEntityRequestInfo
    {
        Experimental::Threading::ConcurrentSharedPtr<EntityId> entityId = nullptr;
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texturePtr = nullptr;
        Experimental::Threading::ConcurrentSharedPtr<MeshInfo> meshPtr = nullptr;
        Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> pipelinePtr = nullptr;
    };
}

#endif // NOVELRT_CREATERENDERENTITYREQUESTINFO_H
