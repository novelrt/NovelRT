// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    EntityCache::EntityCache(size_t poolSize) noexcept : _updateVectors(std::vector<std::vector<EntityId>>(poolSize)), _entitiesToRemoveThisFrame{}, _entityUuidIdentifiers(), _registerVectors(std::vector<std::vector<EntityId>>(poolSize))
    {
    }

    void EntityCache::RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept
    {
        _updateVectors[poolId].push_back(entityToRemove);
    }

    void EntityCache::ProcessEntityDeletionRequestsFromThreads() noexcept
    {
        _entitiesToRemoveThisFrame.clear();
        size_t currentSize = 0;
        for (auto&& vector : _updateVectors)
        {
            _entitiesToRemoveThisFrame.resize(currentSize + vector.size());
            std::copy(vector.begin(), vector.end(), _entitiesToRemoveThisFrame.begin() + currentSize);
            currentSize += vector.size();
            vector.clear();
        }

        for(auto&& id : _entitiesToRemoveThisFrame)
        {
            unused(_entityUuidIdentifiers.TryRemove(id));
        }
    }

    void EntityCache::ProcessEntityRegistrationRequestsFromThreads() noexcept
    {
        std::random_device rd;
        auto seedData = std::array<int, std::mt19937::state_size> {};
        std::generate(std::begin(seedData), std::end(seedData), std::ref(rd));
        std::seed_seq seq(std::begin(seedData), std::end(seedData));
        std::mt19937 generator(seq);
        uuids::uuid_random_generator gen{generator};

        for (auto&& vector : _registerVectors) 
        {
            for(auto&& entity : vector)
            {
                _entityUuidIdentifiers.Insert(entity, gen());
            }
        }
    }

    void EntityCache::RegisterEntity(size_t poolId, EntityId entity)
    {
        _registerVectors[poolId].emplace_back(entity);
    } 
} // namespace NovelRT::Ecs
