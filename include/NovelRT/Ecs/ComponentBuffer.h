// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTBUFFER_H
#define NOVELRT_ECS_COMPONENTBUFFER_H

#include "EcsUtils.h"
#include "SparseSet.h"

namespace NovelRT::Ecs
{
    template<typename T>
    class ComponentBuffer 
    {
        friend class SystemScheduler;

        private:
        SparseSet<EntityId, T, AtomHashFunction> _rootSet;
        SparseSet<size_t, SparseSet<EntityId, T, AtomHashFunction>> _updateSets;
        T _deleteInstructionState;


        public:
        ComponentBuffer(size_t poolSize, T deleteInstructionState) noexcept : _rootSet(SparseSet<EntityId, T, AtomHashFunction>{}), _updateSets(SparseSet<size_t, SparseSet<EntityId, T, AtomHashFunction>>{}), _deleteInstructionState(deleteInstructionState)
        {
            for (size_t i = 0; i < poolSize; i++)
            {
                _updateSets.Insert(i, SparseSet<EntityId, T, AtomHashFunction>{});
            }
        }

        void PrepComponentBuffersForFrame(const std::vector<EntityId>& destroyedEntities) noexcept
        {
            for (EntityId i : destroyedEntities)
            {
                static_cast<void>(_rootSet.TryRemove(i)); //Intentional discard of return value
            }
            
            for (auto [index, sparseSet] : _updateSets)
            {
                for (auto [entity, component] : sparseSet)
                {
                    if (component == _deleteInstructionState)
                    {
                        static_cast<void>(_rootSet.TryRemove(entity)); // intentional discard again.
                    }
                    else if(!_rootSet.ContainsKey(entity))
                    {
                        _rootSet.Insert(entity, component);
                    }
                    else
                    {
                        _rootSet[entity] += component;
                    }
                }
                sparseSet.Clear();
            }
        }

        T GetDeleteInstructionState() const noexcept
        {
            return _deleteInstructionState;
        } 

        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, T component)
        {
            _updateSets[poolId].Insert(entity, component);
        }

        T GetComponent(EntityId entity) const
        {
            return _rootSet[entity];
        }

        bool HasComponent(EntityId entity) const noexcept
        {
            return _rootSet.ContainsKey(entity);
        }

        // clang-format off
        auto begin() const noexcept
        {
            return _rootSet.cbegin();
        }

        auto end() const noexcept
        {
            return _rootSet.cend();
        }
        // clang-format on
    };
}

#endif //!NOVELRT_ECS_COMPONENTBUFFER_H