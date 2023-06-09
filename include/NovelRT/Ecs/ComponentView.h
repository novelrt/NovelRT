// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTVIEW_H
#define NOVELRT_ECS_COMPONENTVIEW_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A thread-aware view into a ComponentBuffer that allows for both reading and writing of data.
     *
     * @tparam TComponent The type of component that this view provides access to.
     */
    template<typename TComponent> class ComponentView
    {
    private:
        size_t _poolId;
        ComponentBuffer<TComponent> _componentBuffer;

    public:
        /**
         * @brief Constructs a new ComponentView with the context of the current thread.
         *
         * @param poolId The thread's pool ID.
         * @param targetBuffer The buffer this view wraps.
         */
        ComponentView(size_t poolId, ComponentBuffer<TComponent> targetBuffer) noexcept
            : _poolId(poolId), _componentBuffer(std::move(targetBuffer))
        {
        }

        /**
         * @brief Pushes a new Component state as an update instruction into the ComponentBuffer with the current thread
         * context.
         *
         * @param entity The EntityId to apply the component update instruction to.
         * @param instructionState The component as an instruction.
         *
         * @exception NovelRT::Core::Exceptions::DuplicateKeyException when multiple update instructions are pushed to
         * this buffer on the same thread.
         * @exception std::out_of_range if the setup of the ComponentView is invalid. See
         * ComponentBuffer::PushComponentUpdateInstruction for more information.
         * @exception std::bad_alloc if there is no more memory available to NovelRT. See
         * SparseSet::Insert for more information.
         */
        void PushComponentUpdateInstruction(EntityId entity, TComponent instructionState)
        {
            _componentBuffer.PushComponentUpdateInstruction(_poolId, entity, instructionState);
        }

        /**
         * @brief A small helper method for adding a component instance in its default state to the given entity.
         *
         * This is exactly the same as ComponentView::PushComponentUpdateInstruction, however it takes the component
         * state as an optional parameter. This allows for an implicit default state to be added to the entity in
         * question.
         *
         * @param entity The EntityId to add the component to.
         * @param initialValue The optional component state to be applied.
         *
         * @exception NovelRT::Core::Exceptions::DuplicateKeyException when multiple update instructions are pushed to
         * this buffer on the same thread.
         */
        void AddComponent(EntityId entity, TComponent initialValue = TComponent{})
        {
            PushComponentUpdateInstruction(entity, initialValue);
        }

        /**
         * @brief Removes the specified component type from a given entity.
         *
         * This is exactly the same as ComponentView::PushComponentUpdateInstruction if it is provided with the
         * component deletion state.
         *
         * @param entity The EntityId to remove the component from.
         *
         * @exception NovelRT::Core::Exceptions::DuplicateKeyException when multiple update instructions are pushed to
         * this buffer on the same thread.
         */
        void RemoveComponent(EntityId entity)
        {
            PushComponentUpdateInstruction(entity, _componentBuffer.GetDeleteInstructionState());
        }

        /**
         * @brief Gets the immutable component state for a delete instruction.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The immutable component state that represents a delete instruction for given type TComponent.
         */
        [[nodiscard]] TComponent GetDeleteInstructionState() const noexcept
        {
            return _componentBuffer.GetDeleteInstructionState();
        }

        /**
         * @brief Attempts to add a new component of the given type to the entity with safety checks to ensure it is an
         * exceptionless operation.
         *
         * This assumes that you have not previously pushed an update instruction to the ComponentBuffer on this thread
         * this frame. If an update instruction was pushed on this thread previously, this will segfault.
         *
         * @param entity The EntityId to attach the component to.
         * @param initialValue The intitial state of the component. If none is provided, it implicitly defaults to the
         * default state of the component.
         * @return true when the component is successfully added.
         * @return false when ComponentBuffer::HasComponent returns true.
         */
        bool TryAddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            if (_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            AddComponent(entity, initialValue);
            return true;
        }

        /**
         * @brief Attempts to remove a component from an entity with safety checks to ensure it is an exceptionless
         * operation.
         *
         * This assumes that you have not previously pushed an update instruction to the ComponentBuffer on this thread
         * this frame. If an update instruction was pushed on this thread previously, this will segfault.
         *
         * @param entity The EntityId
         * @return true if the component was successfully removed.
         * @return false otherwise.
         */
        bool TryRemoveComponent(EntityId entity)
        {
            if (!_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            RemoveComponent(entity);
            return true;
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The EntityId of retrieve the component from.
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         * @exception NovelRT::Core::Exceptions::KeyNotFoundException if the given EntityId is not present within the
         * immutable buffer data for this update cycle.
         */
        [[nodiscard]] TComponent GetComponent(EntityId entity) const
        {
            return _componentBuffer.GetComponent(entity);
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
            return _componentBuffer.HasComponent(entity);
        }

        /**
         * @brief Attempts to get the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The entity to use for fetching the component.
         * @param outComponent The output result for the fetched component, if there is one.
         * @return true if a component was found and returned in outComponent.
         * @return false if no component exists.
         */
        [[nodiscard]] bool TryGetComponent(EntityId entity, TComponent& outComponent) const noexcept
        {
            return _componentBuffer.TryGetComponent(entity, outComponent);
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method. This is considered an unsafe operation. Before calling this, you must guarantee that the
         * provided entity exists in the read-only portion of the underlying buffer. Please see
         * ComponentView::HasComponent for more information.
         *
         * @param entity The EntityId to retrieve the component from.
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         */
        [[nodiscard]] TComponent GetComponentUnsafe(EntityId entity) const noexcept
        {
            return _componentBuffer.GetComponentUnsafe(entity);
        }

        /**
         * @brief Gets the length of the current immutable data snapshot within the buffer.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The length of the data.
         */
        [[nodiscard]] size_t GetImmutableDataLength() const noexcept
        {
            return _componentBuffer.GetImmutableDataLength();
        }

        /**
         * @brief Gets the beginning forward const iterator state for the immutable data from the underlying
         * ComponentBuffer.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] typename SparseSet<EntityId, TComponent>::ConstIterator begin() const noexcept
        {
            return _componentBuffer.begin();
        }

        /**
         * @brief Gets the end forward const iterator state for the immutable data from the underlying ComponentBuffer.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return ComponentBuffer::ConstIterator starting at the end.
         */
        [[nodiscard]] typename SparseSet<EntityId, TComponent>::ConstIterator end() const noexcept
        {
            return _componentBuffer.end();
        }
    };
}

#endif //! NOVELRT_ECS_COMPONENTVIEW_H
