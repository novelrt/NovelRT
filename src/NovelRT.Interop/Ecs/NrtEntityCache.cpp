// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEntityCache.h>
#include <NovelRT/Ecs/EntityCache.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtEntityCache Nrt_EntityCache_Create(size_t poolSize)
    {
        return reinterpret_cast<NrtEntityCache>(new EntityCache(poolSize));
    }

    NrtEntityIdVector Nrt_EntityCache_GetEntitiesToRemoveThisFrame(NrtEntityCache entityCache)
    {
        return reinterpret_cast<NrtEntityIdVector>(
            &reinterpret_cast<EntityCache*>(entityCache)->GetEntitiesToRemoveThisFrame());
    }

    void Nrt_EntityCache_RemoveEntity(NrtEntityCache entityCache, size_t poolId, NrtEntityId entityToRemove)
    {
        reinterpret_cast<EntityCache*>(entityCache)->RemoveEntity(poolId, entityToRemove);
    }

    void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(NrtEntityCache entityCache)
    {
        reinterpret_cast<EntityCache*>(entityCache)->ProcessEntityDeletionRequestsFromThreads();
    }

    NrtResult Nrt_EntityCache_Destroy(NrtEntityCache entityCache)
    {
        if (entityCache == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<EntityCache*>(entityCache);

        return NRT_SUCCESS;
    }
}