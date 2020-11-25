// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_BASESYSTEM_H
#define NOVELRT_ECS_BASESYSTEM_H

#include "EcsUtils.h"
#include "../Atom.h"

namespace NovelRT::Ecs
{
    template<typename T>
    class BaseSystem
    {
        private:

        public:
        virtual void UpdateComponents() = 0;

        void AddComponent(T component, EntityId entity)
        {

        }

        void RemoveComponent(EntityId entity)
        {

        }

        bool HasComponent(EntityId entity)
        {

        }
    };
}

#endif //!NOVELRT_ECS_BASESYSTEM_H