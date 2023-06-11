// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_DefaultRenderingSystem_FindInScheduler(NrtSystemSchedulerHandle scheduler,
                                                         NrtDefaultRenderingSystemHandle* outputResult);

    NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system);

    NrtResult Nrt_DefaultRenderingSystem_GetOrLoadTexture(NrtDefaultRenderingSystemHandle system,
                                                          const char* textureName,
                                                          NrtFutureResultOfTextureInfoHandle* outputTextureFuture);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureById(NrtDefaultRenderingSystemHandle system,
                                                                NrtAtom id,
                                                                NrtTextureInfoHandle* outputTexture);

    NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureByName(NrtDefaultRenderingSystemHandle system,
                                                                  const char* name,
                                                                  NrtTextureInfoHandle* outputTexture);

    // Even after calling a DeleteTexture method, TextureInfo_Destroy still
    // needs to be called by the user once done with it!

    NrtResult Nrt_DefaultRenderingSystem_DeleteTextureByHandle(NrtDefaultRenderingSystemHandle system,
                                                               NrtTextureInfoHandle texture);

    NrtResult Nrt_DefaultRenderingSystem_DeleteTextureByName(NrtDefaultRenderingSystemHandle system, const char* name);

    NrtResult Nrt_DefaultRenderingSystem_DeleteTextureById(NrtDefaultRenderingSystemHandle system, NrtAtom id);

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntity(NrtDefaultRenderingSystemHandle system,
                                                            NrtTextureInfoHandle texture,
                                                            NrtCatalogueHandle catalogue,
                                                            NrtEntityId* outputEntityId);

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntityOutsideOfSystem(NrtDefaultRenderingSystemHandle system,
                                                                           NrtTextureInfoHandle texture,
                                                                           NrtSystemSchedulerHandle scheduler,
                                                                           NrtEntityId* outputEntityId);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
