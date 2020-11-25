// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "EcsUtils.h"

namespace NovelRT::Ecs
{
    class Entity
    {
        private:
        EntityId _entityId;

        public:
        Entity(EntityId id) : _entityId(id) {}

        template<typename T>
        T AddComponent(T initialValue)
        {

        }

        template<typename T>
        T AddComponent()
        {

        }

        template<typename T>
        void RemoveComponent()
        {

        }

        template<typename T>
        bool TryRemoveComponent()
        {
            
        }

        EntityId getEntityId()
        {
            return _entityId;
        }
    };
}