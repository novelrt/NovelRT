// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTBUFFER_H
#define NOVELRT_ECS_COMPONENTBUFFER_H

#include "EcsUtils.h"
#include "../Atom.h"
#include "../Timing/Timestamp.h"
#include "SparseSet.h"
#include <vector>
#include <thread>
#include <map>
#include <queue>

namespace NovelRT::Ecs
{
    enum class ComponentUpdateType : int32_t
    {
        Add = 0,
        Remove = 1
    };

    template<typename T>
    class ComponentBuffer 
    {
        friend class SystemScheduler;

        private:
        struct EntityComponentUpdateObject
        {
            ComponentUpdateType updateType;
            EntityId id;
            T componentData;
        };

        std::vector<SparseSet<EntityId, T, AtomHashFunction>> _ecsDataBuffers;
        std::map<std::thread::id, std::vector<EntityComponentUpdateObject>> _componentUpdateInstructions;

        static inline const size_t MutableBufferId = 0;
        static inline const size_t ImmutableBufferId = 1;

        void ValidateCacheForThread() noexcept
        {
            if (_componentUpdateInstructions.find(std::this_thread::get_id()) == _componentUpdateInstructions.end())
            {
                _componentUpdateInstructions.emplace(std::this_thread::get_id(), std::vector<EntityComponentUpdateObject>{});
            }
        }

        void PrepComponentBuffersForFrame()
        {
        }

        public:
        ComponentBuffer() : _ecsDataBuffers(std::vector<SparseSet<EntityId, T, AtomHashFunction>>{SparseSet<EntityId, T, AtomHashFunction>{}, SparseSet<EntityId, T, AtomHashFunction>{}})
        {

        }

        void AddComponent(EntityId entity, T component) noexcept
        {
            ValidateCacheForThread();
        }

        void RemoveComponent(EntityId entity)
        {
            ValidateCacheForThread();
        }

        T GetComponent(EntityId entity) const
        {
            return _ecsDataBuffers.at(ImmutableBufferId)[entity];
        }

        bool HasComponent(EntityId entity) const noexcept
        {
            return _ecsDataBuffers.at(ImmutableBufferId).ContainsKey(entity);
        }
    };
}

#endif //!NOVELRT_ECS_COMPONENTBUFFER_H