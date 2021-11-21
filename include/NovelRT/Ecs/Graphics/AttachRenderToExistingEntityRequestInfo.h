// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ATTACHRENDERTOEXISTINGENTITYREQUESTINFO_H
#define NOVELRT_ATTACHRENDERTOEXISTINGENTITYREQUESTINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct AttachRenderToExistingEntityRequestInfo
    {
        EntityId entityId = 0;
        Experimental::Threading::ConcurrentSharedPtr<TextureInfo> texturePtr = nullptr;
        Experimental::Threading::ConcurrentSharedPtr<VertexInfo> meshPtr = nullptr;
        Experimental::Threading::ConcurrentSharedPtr<GraphicsPipelineInfo> pipelinePtr = nullptr;
    };
}

#endif // NOVELRT_ATTACHRENDERTOEXISTINGENTITYREQUESTINFO_H
