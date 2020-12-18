// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_ENTITY

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
        void AddComponent(T initialValue = T{}) //TODO: Should this be noexcept?
        {
            _catalogue->AddComponent<T>(_entityId, initialValue);
        }

        template<typename T>
        bool TryAddComponent(T initialValue = T{}) noexcept
        {
            return _catalogue->TryAddComponent<T>(_entityId, initialValue);
        }

        template<typename T>
        void RemoveComponent()
        {
            _catalogue->RemoveComponent<T>(_entityId);
        }

        template<typename T>
        bool HasComponent() const noexcept
        {
            _catalogue->Has
        }

        template<typename T>
        bool TryRemoveComponent() noexcept
        {
            
        }

        EntityId getEntityId()
        {
            return _entityId;
        }
    };
}

#endif //!NOVELRT_ECS_ENTITY