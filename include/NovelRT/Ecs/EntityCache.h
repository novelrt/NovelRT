// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_ENTITYCACHE_H
#define NOVELRT_ECS_ENTITYCACHE_H

#include "EcsUtils.h"
#include "SparseSet.h"
#include <vector>

namespace NovelRT::Ecs
{
    class EntityCache
    {
        private:
        SparseSet<size_t, std::vector<EntityId>> _updateVectors;
        std::vector<EntityId> _entitiesToRemoveThisFrame;

        public:
        EntityCache(size_t poolSize) noexcept;

        inline const std::vector<EntityId>& GetEntitiesToRemoveThisFrame() const noexcept
        {
            return _entitiesToRemoveThisFrame;
        }

        void RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept;

        void ProcessEntityDeletionRequestsFromThreads() noexcept;
    };
}

#endif //!NOVELRT_ECS_ENTITYCACHE_H