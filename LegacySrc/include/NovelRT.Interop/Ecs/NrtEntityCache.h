// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_ENTITYCACHE_H
#define NOVELRT_INTEROP_ECS_ENTITYCACHE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtEntityCacheHandle Nrt_EntityCache_Create(size_t poolSize);

    NrtEntityIdVectorHandle Nrt_EntityCache_GetEntitiesToRemoveThisFrame(NrtEntityCacheHandle entityCache);

    void Nrt_EntityCache_RemoveEntity(NrtEntityCacheHandle entityCache, size_t poolId, NrtEntityId entityToRemove);

    void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(NrtEntityCacheHandle entityCache);

    NrtResult Nrt_EntityCache_Destroy(NrtEntityCacheHandle entityCache);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_ENTITYCACHE_H
