// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_NRTDEFAULTRENDERINGSYSTEM_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_NRTDEFAULTRENDERINGSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_DefaultRenderingSystem_FindInScheduler(NrtSystemSchedulerHandle scheduler,
                                                         NrtDefaultRenderingSystemHandle* outputResult);

    NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system);

    // TODO: Implement GetOrLoadTexture, CreateSpriteEntity and CreateSpriteEntityOutsideOfSystem

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_NRTDEFAULTRENDERINGSYSTEM_H
