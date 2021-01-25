// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.h>

namespace NovelRT::Ecs
{
    Catalogue::Catalogue(size_t poolId, ComponentCache& componentCache, EntityCache& entityCache) noexcept
        : _poolId(poolId),
          _componentCache(componentCache),
          _entityCache(entityCache),
          _createdEntitiesThisFrame(std::vector<EntityId>{})
    {
    }

    EntityId Catalogue::CreateEntity() noexcept
    {
        EntityId returnId = Atom::getNextEntityId();
        _createdEntitiesThisFrame.push_back(returnId);
        return returnId;
    }

    void Catalogue::DeleteEntity(EntityId entity) noexcept
    {
        if (std::find(_createdEntitiesThisFrame.begin(), _createdEntitiesThisFrame.end(), entity) !=
            _createdEntitiesThisFrame.end())
        {
            return;
        }

        _entityCache.RemoveEntity(_poolId, entity);
    }

} // namespace NovelRT::Ecs