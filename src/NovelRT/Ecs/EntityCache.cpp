// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    EntityCache::EntityCache(size_t poolSize) noexcept
        : _removalUpdateVectors(std::vector<std::vector<EntityId>>(poolSize)),
          _registrationUpdateVectors(std::vector<std::vector<EntityId>>(poolSize))
    {
    }

    void EntityCache::AddEntity(size_t poolId, EntityId newEntity) noexcept
    {
        _registrationUpdateVectors[poolId].push_back(newEntity);
    }

    void EntityCache::RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept
    {
        _removalUpdateVectors[poolId].push_back(entityToRemove);
        _removalUpdateVectors[poolId].erase(std::remove(_registrationUpdateVectors[poolId].begin(),
                                                        _registrationUpdateVectors[poolId].end(), entityToRemove),
                                            _registrationUpdateVectors[poolId].end());
    }

    void EntityCache::ProcessEntityDeletionRequestsFromThreads() noexcept
    {
        _entitiesToRemoveThisFrame.clear();
        size_t currentSize = 0;

        for (auto&& vector : _removalUpdateVectors)
        {
            size_t oldSize = currentSize;
            currentSize += vector.size();
            _entitiesToRemoveThisFrame.resize(currentSize);
            auto rootIt = _entitiesToRemoveThisFrame.begin();
            std::advance(rootIt, oldSize);
            std::copy(vector.begin(), vector.end(), rootIt);
            vector.clear();
        }
    }

    void EntityCache::ProcessEntityRegistrationRequestsFromThreads() noexcept
    {
        size_t currentSize = _registeredEntities.size();

        for (auto&& vector : _registrationUpdateVectors)
        {
            if (vector.empty())
            {
                continue;
            }

            size_t oldSize = currentSize;
            currentSize += vector.size();
            _registeredEntities.resize(currentSize);
            auto rootIt = _registeredEntities.begin();
            std::advance(rootIt, oldSize);
            std::copy_if(vector.begin(), vector.end(), rootIt, [&](auto entity) -> bool {
                return std::find(_registeredEntities.begin(), _registeredEntities.end(), entity) ==
                       _registeredEntities.end();
            });
            vector.clear();
        }
    }

    void EntityCache::ApplyEntityDeletionRequestsToRegisteredEntities() noexcept
    {
        for (auto&& entity : _entitiesToRemoveThisFrame)
        {
            _registeredEntities.erase(std::remove(_registeredEntities.begin(), _registeredEntities.end(), entity),
                                      _registeredEntities.end());
        }
    }
} // namespace NovelRT::Ecs