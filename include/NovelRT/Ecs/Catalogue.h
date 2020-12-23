// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_CATALOGUE_H
#define NOVELRT_ECS_CATALOGUE_H

#include "ComponentCache.h"
#include "EcsUtils.h"
#include "SystemScheduler.h"
#include "SparseSet.h"

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

    template <typename TComponent>
    class ComponentView
    {
        private:
        size_t _poolId;
        ComponentBuffer<TComponent>& _componentBuffer;
        
        public:
        ComponentView(size_t poolId, ComponentBuffer<TComponent>& targetBuffer) noexcept : _poolId(poolId), _componentBuffer(targetBuffer) {}

        // clang-format off
        auto begin() const noexcept
        {
            return _componentBuffer.begin();
        }

        auto end() const noexcept
        {
            return _componentBuffer.end();
        }
    };

    class Catalogue
    {
        private:
        size_t _poolId;
        ComponentCache& _cache;

        public:
        Catalogue(size_t poolId, ComponentCache& componentCache) noexcept : _poolId(poolId), _cache(componentCache)
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

        template<typename... TComponents>
        auto GetComponentView()
        {
            return std::tie(ComponentView<TComponents>(_poolId, _cache.GetComponentBuffer<TComponents>())...);
        }

        template<typename T>
        void AddComponent(EntityId entity, T componentData)
        {
            _cache.GetComponentBuffer<T>().AddComponent(entity, componentData);
        }

        template<typename T>
        bool TryAddComponent(EntityId entity, T componentData) noexcept
        {
            ComponentBuffer<T>& buffer = _cache.GetComponentBuffer<T>();
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
            _cache.GetComponentBuffer<T>().RemoveComponent(entity);
        }

        template<typename T>
        bool TryRemoveComponent(EntityId entity) noexcept
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
            return _cache.GetComponentBuffer<T>().HasComponent(entity);
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