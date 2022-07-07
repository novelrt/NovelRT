// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEntityCache.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtEntityCacheHandle Nrt_EntityCache_Create(size_t poolSize)
    {
        return reinterpret_cast<NrtEntityCacheHandle>(new EntityCache(poolSize));
    }

    NrtEntityIdVectorHandle Nrt_EntityCache_GetEntitiesToRemoveThisFrame(NrtEntityCacheHandle entityCache)
    {
        return reinterpret_cast<NrtEntityIdVectorHandle>(
            &reinterpret_cast<EntityCache*>(entityCache)->GetEntitiesToRemoveThisFrame());
    }

    void Nrt_EntityCache_RemoveEntity(NrtEntityCacheHandle entityCache, size_t poolId, NrtEntityId entityToRemove)
    {
        reinterpret_cast<EntityCache*>(entityCache)->RemoveEntity(poolId, entityToRemove);
    }

    void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(NrtEntityCacheHandle entityCache)
    {
        reinterpret_cast<EntityCache*>(entityCache)->ProcessEntityDeletionRequestsFromThreads();
    }

    NrtResult Nrt_EntityCache_Destroy(NrtEntityCacheHandle entityCache)
    {
        if (entityCache == nullptr)
        {
            Nrt_setErrIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<EntityCache*>(entityCache);

        return NRT_SUCCESS;
    }
}
