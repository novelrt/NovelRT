// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_BASESYSTEM_H
#define NOVELRT_ECS_BASESYSTEM_H

#include "EcsUtils.h"
#include "../Atom.h"
#include "../Timing/Timestamp.h"
#include "SparseSet.h"
#include <vector>
#include <thread>
#include <map>

namespace NovelRT::Ecs
{
    enum class ComponentUpdateType : int32_t
    {
        Invalid = -1,
        Add = 0,
        Remove = 1
    };

    template<typename T>
    class BaseSystem
    {
        friend class SystemScheduler;

        private:
        struct EntityComponentUpdateObject
        {
            ComponentUpdateType updateType;
            EntityId id;
            T componentData;
        };

        std::vector<SparseSet<EntityId, T>> _ecsDataBuffers;
        std::map<std::thread::id, std::vector<EntityComponentUpdateObject>> _componentUpdateInstructions;

        size_t _mutableBufferId = 0; // TODO: Move to ctor

        void UpdateComponentBuffer(Timing::Timestamp deltaTime)
        {
            UpdateComponents(deltaTime, _ecsDataBuffers.at(_mutableBufferId));
        }

        void ValidateCacheForThread() noexcept
        {
            if (_componentUpdateInstructions.find(std::this_thread::get_id()) == _componentUpdateInstructions.end())
            {
                _componentUpdateInstructions.emplace(std::this_thread::get_id(), std::vector<EntityComponentUpdateObject>{});
            }
        }

        protected:
        virtual void UpdateComponents(Timing::Timestamp deltaTime, SparseSet<EntityId, T>& componentData) = 0;

        public:
        void AddComponent(T component, EntityId entity) noexcept
        {
            ValidateCacheForThread();
            EntityComponentUpdateObject objectToPass { ComponentUpdateType::Add, entity, component };
            _componentUpdateInstructions[std::this_thread::get_id()].emplace_back(objectToPass);
        }

        void RemoveComponent(EntityId entity)
        {
            ValidateCacheForThread();
            EntityComponentUpdateObject objectToPass { ComponentUpdateType::Remove, entity, T{} };
            _componentUpdateInstructions[std::this_thread::get_id()].emplace_back(objectToPass);
        }

        bool HasComponent(EntityId entity) const noexcept
        {

        }
    };
}

#endif //!NOVELRT_ECS_BASESYSTEM_H