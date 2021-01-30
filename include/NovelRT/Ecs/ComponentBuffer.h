// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTBUFFER_H
#define NOVELRT_ECS_COMPONENTBUFFER_H

#include "EcsUtils.h"
#include "SparseSet.h"

namespace NovelRT::Ecs
{
    /**
     * @brief A storage type that manages the storage and modification of the given type concurrently. You should not be
     * instantiating this yourself in a regular setup.
     *
     * Please note that this storage type assumes that the component in question is a simple struct at all times.
     * You should not have component types that are massively complex as there may be many copy instructions that are
     * not SIMDifiable if the type is too complicated. The type in question will need to have addition and an equality
     * comparison operator implemented in order for it to function as a type a ComponentBuffer can manage for you.
     *
     * @tparam T The type of component this ComponentBuffer will manage.
     */
    template<typename T> class ComponentBuffer
    {
    private:
        SparseSet<EntityId, T, AtomHashFunction> _rootSet;
        SparseSet<size_t, SparseSet<EntityId, T, AtomHashFunction>> _updateSets;
        T _deleteInstructionState;

    public:
        /**
         * @brief Constructs a new ComponentBuffer for type T.
         *
         *
         * @param poolSize The amount of worker threads being utilised in this instance of the ECS.
         * @param deleteInstructionState The component state to treat as the delete instruction. When this state is
         * passed in during an update, the ComponentBuffer will delete the component from the target entity during
         * resolution.
         */
        ComponentBuffer(size_t poolSize, T deleteInstructionState) noexcept
            : _rootSet(SparseSet<EntityId, T, AtomHashFunction>{}),
              _updateSets(SparseSet<size_t, SparseSet<EntityId, T, AtomHashFunction>>{}),
              _deleteInstructionState(deleteInstructionState)
        {
            for (size_t i = 0; i < poolSize; i++)
            {
                _updateSets.Insert(i, SparseSet<EntityId, T, AtomHashFunction>{});
            }
        }

        /**
         * @brief Handles all modification instructions from all threads and clears the instruction sets in preparation
         * for new instructions incoming for the next update iteration.
         *
         * In a regular ECS setup, you should not have to call this yourself. Please also note that this is not thread
         * safe. Usually, this method is only called by the main thread, and only while no work is currently being
         * processed.
         *
         * @param destroyedEntities The entities that have been explicitly destroyed by all worker threads during the
         * last update cycle.
         */
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
                    else if (!_rootSet.ContainsKey(entity))
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

        /**
         * @brief Gets the delete instruction state for type T.
         *
         * If this state is pushed in as an update instruction, the entity in question will no longer have this
         * component attached and the component will be deleted. This is a pure method. Calling this without using the
         * result has no effect and introduces overhead for calling a method.
         *
         * @return T in the specified state that represents deletion.
         */
        [[nodiscard]] T GetDeleteInstructionState() const noexcept
        {
            return _deleteInstructionState;
        }

        /**
         * @brief Pushes in an update instruction for the given entity, component and thread pool ID.
         *
         * @param poolId The pool ID associated with the thread attempting to push the update instruction.
         * @param entity The target entity within this particular ECS instance.
         * @param component The instruction as a component state. This should represent the modification you wish to
         * make, as opposed to a final state.
         *
         * @exception Exceptions::DuplicateKeyException if multiple updates to the same entity are pushed.
         */
        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, T component)
        {
            _updateSets[poolId].Insert(entity, component);
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity
         * @return T A copy of the current state of the component attached to the given entity.
         * @exception std::out_of_range if the given EntityId is not present within the set.
         */
        [[nodiscard]] T GetComponent(EntityId entity) const
        {
            return _rootSet[entity];
        }

        /**
         * @brief Verifies if a given entity has a component.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The target entity to check for an attached component on.
         * @return true if the immutable data contains the given EntityId.
         * @return false if there is no entry for the given EntityId.
         */
        [[nodiscard]] bool HasComponent(EntityId entity) const noexcept
        {
            return _rootSet.ContainsKey(entity);
        }

        /**
         * @brief Gets the length of the current immutable data snapshot within the buffer.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return size_t The length of the data.
         */
        [[nodiscard]] size_t GetImmutableDataLength() const noexcept
        {
            return _rootSet.Length();
        }

        // clang-format off

        /**
         * @brief Gets the beginning forward const iterator state for the immutable data in this ComponentBuffer.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] auto begin() const noexcept
        {
            return _rootSet.cbegin();
        }

        /**
         * @brief Gets the end forward const iterator state for the immutable data in this ComponentBuffer.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] auto end() const noexcept
        {
            return _rootSet.cend();
        }

        // clang-format on
    };
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_COMPONENTBUFFER_H