// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTENTITYCACHE_H
#define NOVELRT_NRTENTITYCACHE_H

#include "../Timing/NrtTimestamp.h"
#include "../NrtInteropUtils.h"
#include "NrtEcsUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct EntityCacheHandle* NrtEntityCache;

    NrtEntityCache Nrt_EntityCache_Create(size_t poolSize);

    NrtEntityIdVector Nrt_EntityCache_GetEntitiesToRemoveThisFrame(NrtEntityCache entityCache);

    void Nrt_EntityCache_RemoveEntity(NrtEntityCache entityCache, NrtEntityId entityToRemove);

    void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(NrtEntityCache entityCache);

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTENTITYCACHE_H
