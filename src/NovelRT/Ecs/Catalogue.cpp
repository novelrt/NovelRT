// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

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
        static NovelRT::Core::AtomFactory& _entityIdFactory = NovelRT::Core::AtomFactoryDatabase::GetFactory("EntityId");
        auto& knownEntities = _entityCache.GetRegisteredEntities();

        EntityId returnId = _entityIdFactory.GetNext();

        while (std::find(knownEntities.begin(), knownEntities.end(), returnId) != knownEntities.end())
        {
            returnId = _entityIdFactory.GetNext();
        }

        _entityCache.AddEntity(_poolId, returnId);
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

    UnsafeComponentView Catalogue::GetComponentViewById(ComponentTypeId componentTypeId)
    {
        return UnsafeComponentView(_poolId, _componentCache.GetComponentBufferById(componentTypeId));
    }
} // namespace NovelRT::Ecs
