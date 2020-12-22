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
    template<typename T>
    class ComponentBuffer 
    {
        friend class SystemScheduler;

        private:
        SparseSet<EntityId, T, AtomHashFunction> _rootSet;
        SparseSet<size_t, SparseSet<EntityId, T, AtomHashFunction>> _updateSets;

        void PrepComponentBuffersForFrame()
        {
            for (auto [index, sparseSet] : _updateSets)
            {
                sparseSet.Clear();
            }
        }

        public:
        ComponentBuffer(size_t poolSize) noexcept : _rootSet(SparseSet<EntityId, T, AtomHashFunction>{}), _updateSets(SparseSet<std::thread::id, SparseSet<EntityId, T, AtomHashFunction>>{})
        {
            for (size_t i = 0; i < poolSize; i++)
            {
                _updateSets.Insert(i, SparseSet<EntityId, T, AtomHashFunction>{});
            }
        }

        void AddComponent(size_t poolId, EntityId entity, T component)
        {
            _updateSets[poolId].Insert(entity, component);
        }

        void RemoveComponent(size_t poolId, EntityId entity)
        {
            _updateSets[poolId].Remove(entity);
        }

        T GetComponent(EntityId entity) const
        {
            return _ecsDataBuffers.at(ImmutableBufferId)[entity];
        }

        bool HasComponent(EntityId entity) const noexcept
        {
            return _ecsDataBuffers.at(ImmutableBufferId).ContainsKey(entity);
        }

        // clang-format off
        auto begin() const noexcept
        {
            return _rootSet.begin();
        }

        auto end() const noexcept
        {
            return _rootSet.end();
        }
        // clang-format on
    };
}

#endif //!NOVELRT_ECS_COMPONENTBUFFER_H