// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EntityCache.h>

namespace NovelRT::Ecs
{
    EntityCache::EntityCache(size_t poolSize) noexcept : _updateVectors(SparseSet<size_t, std::vector<EntityId>>())
    {
        for (size_t i = 0; i < poolSize; i++)
        {
            _updateVectors.Insert(i, std::vector<EntityId>{});
        }
    }

    void EntityCache::RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept
    {
        _updateVectors[poolId].push_back(entityToRemove);
    }

    void EntityCache::ProcessEntityDeletionRequestsFromThreads() noexcept
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
} // namespace NovelRT::Ecs