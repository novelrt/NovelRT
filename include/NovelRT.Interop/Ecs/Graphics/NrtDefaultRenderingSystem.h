// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultRenderingSystemHandle Nrt_DefaultRenderingSystem_create(
            NrtIGraphicsPluginProviderPtrHandle graphicsPluginProvider,
            NrtIWindowingPluginProviderPtrHandle windowingPluginProvider,
            NrtIResourceManagementPluginProviderPtrHandle resourceManagementPluginProvider);

    NrtResult Nrt_DefaultRenderingSystem_destroy(NrtDefaultRenderingSystemHandle system);

    NrtResult Nrt_DefaultRenderingSystem_Update(
            NrtDefaultRenderingSystemHandle system,
            NrtTimestamp delta,
            NrtCatalogueHandle catalogue);

    NrtResult Nrt_DefaultRenderingSystem_GetOrLoadTexture(
            NrtDefaultRenderingSystemHandle system,
            const char* spriteName,
            NrtTextureInfoFutureResultHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureBasedOnId(
            NrtDefaultRenderingSystemHandle system,
            NrtAtom ecsId,
            NrtTextureInfoThreadedPtrHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_LoadVertexDataRawUntyped(
            NrtDefaultRenderingSystemHandle system,
            const char* vertexDataName,
            void* data,
            size_t dataTypeSize,
            size_t dataLength,
            NrtVertexInfoFutureResultHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnName(
            NrtDefaultRenderingSystemHandle system,
            const char* vertexDataName,
            NrtVertexInfoThreadedPtrHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnId(
            NrtDefaultRenderingSystemHandle system,
            NrtAtom ecsId,
            NrtVertexInfoThreadedPtrHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingPipelineInfoBasedOnId(
            NrtDefaultRenderingSystemHandle system,
            NrtAtom ecsId,
            NrtGraphicsPipelineInfoThreadedPtrHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_RegisterPipeline(
            NrtDefaultRenderingSystemHandle system,
            const char* pipelineName,
            NrtGraphicsPipelinePtrHandle pipeline,
            NrtGraphicsResourceMemoryVectorHandle customConstantBufferRegions,
            NrtBool useEcsTransforms,
            NrtGraphicsPipelineInfoThreadedPtrHandle *output);

    NrtResult Nrt_DefaultRenderingSystem_AttachSpriteRenderingToEntity(
            NrtDefaultRenderingSystemHandle system,
            NrtEntityId entity,
            NrtTextureInfoThreadedPtrHandle texture,
            NrtCatalogueHandle catalogue);

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntity(
            NrtDefaultRenderingSystemHandle system,
            NrtTextureInfoThreadedPtrHandle texture,
            NrtCatalogueHandle catalogue,
            NrtEntityId *output);

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntityOutsideOfSystem(
            NrtDefaultRenderingSystemHandle system,
            NrtTextureInfoThreadedPtrHandle texture,
            NrtSystemSchedulerHandle scheduler,
            NrtEntityId *output);

    NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
