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

        void PrepComponentBufferForFrame(const std::vector<EntityId>& destroyedEntities) noexcept
        {
            for (EntityId i : destroyedEntities)
            {
                _rootSet.TryRemove(i);
            }
            
            for (auto [index, sparseSet] : _updateSets)
            {
                for (auto [entity, component] : sparseSet)
                {
                    if (component == _deleteInstructionState)
                    {
                        _rootSet.TryRemove(entity); 
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

        [[nodiscard]] T GetDeleteInstructionState() const noexcept
        {
            return _deleteInstructionState;
        } 

        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, T component)
        {
            _updateSets[poolId].Insert(entity, component);
        }

        [[nodiscard]] T GetComponent(EntityId entity) const
        {
            return _rootSet[entity];
        }

        [[nodiscard]] bool HasComponent(EntityId entity) const noexcept
        {
            return _rootSet.ContainsKey(entity);
        }

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept
        {
            return _rootSet.Length();
        }

        // clang-format off
        [[nodiscard]] auto begin() const noexcept
        {
            return _rootSet.cbegin();
        }

        [[nodiscard]] auto end() const noexcept
        {
            return _rootSet.cend();
        }
        // clang-format on
    };
}

#endif //!NOVELRT_ECS_COMPONENTBUFFER_H