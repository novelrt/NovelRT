
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_ENTITYCACHE_H
#define NOVELRT_ECS_ENTITYCACHE_H

#include "EcsUtils.h"
#include "SparseSet.h"
#include <algorithm>

namespace NovelRT::Ecs
{
    class EntityCache
    {
        private:
        SparseSet<size_t, std::vector<EntityId>> _updateVectors;
        std::vector<EntityId> _entitiesToRemoveThisFrame;

        public:
        EntityCache(size_t poolSize) noexcept : _updateVectors(SparseSet<size_t, std::vector<EntityId>>())
        {
            for (size_t i = 0; i < poolSize; i++)
            {
                _updateVectors.Insert(i, std::vector<EntityId>{});
            }
        }

        const std::vector<EntityId>& GetEntitiesToRemoveThisFrame() const noexcept
        {
            return _entitiesToRemoveThisFrame;
        }

        void RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept
        {
            _updateVectors[poolId].push_back(entityToRemove);
        }

        void ProcessEntityDeletionRequestsFromThreads() noexcept
        {
            _entitiesToRemoveThisFrame.clear();
            size_t currentSize = 0;
            for (auto&& [poolId, vector] : _updateVectors)
            {
                _entitiesToRemoveThisFrame.resize(currentSize + vector.size());
                std::copy(vector.begin(), vector.end(), _entitiesToRemoveThisFrame.begin() + currentSize);
                currentSize += vector.size();
                vector.clear();
            }
        }
    };
}

#endif //!NOVELRT_ECS_ENTITYCACHE_H