// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_CATALOGUE_H
#define NOVELRT_ECS_CATALOGUE_H

#include "ComponentCache.h"
#include "EcsUtils.h"

namespace NovelRT::Ecs
{
    class Catalogue;
    class Entity
    {
        private:
        EntityId _entityId;
        Catalogue* _catalogue;

        public:
        Entity(EntityId id, Catalogue* catalogue) : _entityId(id), _catalogue(catalogue) {}

        template<typename T>
        void AddComponent(T initialValue = T{}); //TODO: Should this be noexcept?

        template<typename T>
        bool TryAddComponent(T initialValue = T{}) noexcept;

        template<typename T>
        void RemoveComponent();

        template<typename T>
        bool TryRemoveComponent() noexcept;
        
        template<typename T>
        bool HasComponent() const noexcept;

        inline EntityId getEntityId() const noexcept
        {
            return _entityId;
        }
    };

    class Catalogue
    {
        private:
        inline static size_t TotalCatalogueCount = 0;
        size_t _catalogueId;

        public:
        Catalogue() noexcept : _catalogueId(TotalCatalogueCount++)
        {

        }

        inline Entity CreateEntity() noexcept
        {
            return Entity(Atom::getNextEntityId(), this);
        }

        inline Entity GetEntityAsObject(EntityId entityId)
        {
            return Entity(entityId, this);
        }

        template<typename T>
        void AddComponent(EntityId entity, T componentData)
        {
            ComponentCache::GetComponentBuffer<T>(_catalogueId).AddComponent(entity, componentData);
        }

        template<typename T>
        bool TryAddComponent(EntityId entity, T componentData) noexcept
        {
            ComponentBuffer<T>& buffer = ComponentCache::GetComponentBuffer<T>(_catalogueId);
            if (buffer.HasComponent(entity))
            {
                return false;
            }

            buffer.AddComponent(entity, componentData);
            return true;
        }

        template<typename T>
        void RemoveComponent(EntityId entity)
        {
            ComponentCache::GetComponentBuffer<T>(_catalogueId).RemoveComponent(entity);
        }

        template<typename T>
        bool TryRemoveComponent(EntityId entity)
        {
            ComponentBuffer<T>& buffer = ComponentCache::GetComponentBuffer<T>(_catalogueId);
            if (!buffer.HasComponent(entity))
            {
                return false;
            }

            buffer.RemoveComponent(entity);
            return true;
        }

        template<typename T>
        bool HasComponent(EntityId entity) const noexcept
        {
            return ComponentCache::GetComponentBuffer<T>(_catalogueId).HasComponent(entity);
        }
    };

    template<typename T>
    void Entity::AddComponent(T initialValue)
    {
        _catalogue->AddComponent<T>(_entityId, initialValue);
    }

    template<typename T>
    bool Entity::TryAddComponent(T initialValue) noexcept
    {
        return _catalogue->TryAddComponent<T>(_entityId, initialValue);
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        _catalogue->RemoveComponent<T>(_entityId);
    }

    template<typename T>
    bool Entity::TryRemoveComponent() noexcept
    {
        return _catalogue->TryRemoveComponent<T>(_entityId);
    }

    template<typename T>
    bool Entity::HasComponent() const noexcept
    {
        return _catalogue->HasComponent<T>(_entityId);
    }
}
#endif //!NOVELRT_ECS_CATALOGUE_H