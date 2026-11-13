#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>

#include <cstddef>
#include <utility>

namespace NovelRT::Ecs
{
    template<typename TComponent>
    class ComponentBuffer;
    template<typename, typename>
    class SparseSet;

    /**
     * @brief A thread-aware view into a ComponentBuffer that allows for both reading and writing of data.
     *
     * @tparam TComponent The type of component that this view provides access to.
     */
    template<typename TComponent>
    class ComponentView
    {
    private:
        size_t _poolId;
        ComponentBuffer<TComponent> _componentBuffer;
        const EntityAllocator* _entityAllocator;

    public:
        /**
         * @brief Constructs a new ComponentView with the context of the current thread.
         *
         * @param poolId The thread's pool ID.
         * @param targetBuffer The buffer this view wraps.
         * @param entityAllocator The allocator used to validate entity handles.
         */
        ComponentView(size_t poolId,
                      ComponentBuffer<TComponent> targetBuffer,
                      const EntityAllocator& entityAllocator) noexcept
            : _poolId(poolId), _componentBuffer(std::move(targetBuffer)), _entityAllocator(&entityAllocator)
        {
        }

        /**
         * @brief Pushes a new Component state as an update instruction into the ComponentBuffer with the current thread
         * context.
         *
         * @param entity The EntityId to apply the component update instruction to.
         * @param instructionState The component as an instruction.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void PushComponentUpdateInstruction(EntityId entity, TComponent instructionState)
        {
            PushComponentUpdateInstruction(_entityAllocator->CreateHandleForAllocated(entity), instructionState);
        }

        /**
         * @brief Validates an entity handle and queues a component update for ECS synchronisation.
         *
         * @param entity The handle identifying the entity to update.
         * @param instructionState The component update instruction.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void PushComponentUpdateInstruction(const EntityHandle& entity, TComponent instructionState)
        {
            if (!_entityAllocator->IsValid(entity))
            {
                throw Exceptions::KeyNotFoundException();
            }

            _componentBuffer.PushComponentUpdateInstruction(_poolId, entity.Id, instructionState);
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
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void AddComponent(EntityId entity, TComponent initialValue = TComponent{})
        {
            AddComponent(_entityAllocator->CreateHandleForAllocated(entity), initialValue);
        }

        /**
         * @brief A small helper method for adding a component instance in its default state to the given entity.
         *
         * This is exactly the same as ComponentView::PushComponentUpdateInstruction, however it takes the component
         * state as an optional parameter. This allows for an implicit default state to be added to the entity in
         * question.
         *
         * @param entity The EntityHandle& to add the component to.
         * @param initialValue The optional component state to be applied.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void AddComponent(const EntityHandle& entity, TComponent initialValue = TComponent{})
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
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void RemoveComponent(EntityId entity)
        {
            RemoveComponent(_entityAllocator->CreateHandleForAllocated(entity));
        }

        /**
         * @brief Removes the specified component type from a given entity.
         *
         * This is exactly the same as ComponentView::PushComponentUpdateInstruction if it is provided with the
         * component deletion state.
         *
         * @param entity The Entityhandle& to remove the component from.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        void RemoveComponent(const EntityHandle& entity)
        {
            PushComponentUpdateInstruction(entity, _componentBuffer.GetDeleteInstructionState());
        }

        /**
         * @brief Removes all components of the given type from the ECS simulation.
         */
        void RemoveAllComponents()
        {
            for (auto&& [entity, component] : *this)
            {
                RemoveComponent(entity);
            }
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
         * @brief Attempts to queue a component addition for the entity currently allocated with the given ID.
         *
         * @param entity The EntityId to attach the component to.
         * @param initialValue The initial state of the component. If none is provided, it implicitly defaults to the
         * default state of the component.
         *
         * @return true when the component is successfully added.
         * @return false when ComponentBuffer::HasComponent returns true or if the entity does not exist.
         */
        bool TryAddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            // TODO: Wow this sucks. - Matt J.
            EntityHandle handle{};

            try
            {
                handle = _entityAllocator->CreateHandleForAllocated(entity);
            }
            catch (...)
            {
                return false;
            }

            return TryAddComponent(handle, initialValue);
        }

        /**
         * @brief Attempts to queue a component addition for the entity currently allocated with the given ID.
         *
         * @param entity The EntityHandle& to attach the component to.
         * @param initialValue The initial state of the component. If none is provided, it implicitly defaults to the
         * default state of the component.
         *
         * @return true when the component is successfully added.
         * @return false when ComponentBuffer::HasComponent returns true or if the entity does not exist.
         */
        bool TryAddComponent(const EntityHandle& entity, TComponent initialValue = TComponent{}) noexcept
        {
            if (!_entityAllocator->IsValid(entity) || _componentBuffer.HasComponent(entity.Id))
            {
                return false;
            }

            AddComponent(entity, initialValue);
            return true;
        }

        /**
         * @brief Attempts to queue component removal for the entity currently allocated with the given ID.
         *
         * @param entity The EntityId to remove the component from.
         *
         * @return true if the component was successfully removed.
         * @return false otherwise.
         */
        bool TryRemoveComponent(EntityId entity) noexcept
        {
            // TODO: Wow this sucks. - Matt J.
            EntityHandle handle{};

            try
            {
                handle = _entityAllocator->CreateHandleForAllocated(entity);
            }
            catch (...)
            {
                return false;
            }

            return TryRemoveComponent(handle);
        }

        /**
         * @brief Attempts to queue component removal for the entity currently allocated with the given ID.
         *
         * @param entity The EntityHandle& to remove the component from.
         *
         * @return true if the component was successfully removed.
         * @return false otherwise.
         */
        bool TryRemoveComponent(const EntityHandle& entity) noexcept
        {
            if (!_entityAllocator->IsValid(entity) || !_componentBuffer.HasComponent(entity.Id))
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
         * @param entity The EntityId to retrieve the component from.
         *
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        [[nodiscard]] TComponent GetComponent(EntityId entity) const
        {
            return GetComponent(_entityAllocator->CreateHandleForAllocated(entity));
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The EntityHandle& to retrieve the component from.
         *
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        [[nodiscard]] TComponent GetComponent(const EntityHandle& entity) const
        {
            if (!_entityAllocator->IsValid(entity))
            {
                throw Exceptions::KeyNotFoundException();
            }

            return _componentBuffer.GetComponent(entity.Id);
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
            // TODO: This sucks. - Matt J.
            EntityHandle handle{};

            try
            {
                handle = _entityAllocator->CreateHandleForAllocated(entity);
            }
            catch (...)
            {
                return false;
            }

            return HasComponent(handle);
        }

        /**
         * @brief Verifies if a given entity has a component.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The target entity to check for an attached component on.
         * @return true if the immutable data contains the given EntityHandle&.
         * @return false if there is no entry for the given EntityHandle&.
         */
        [[nodiscard]] bool HasComponent(const EntityHandle& entity) const noexcept
        {
            return _entityAllocator->IsValid(entity) && _componentBuffer.HasComponent(entity.Id);
        }

        /**
         * @brief Attempts to get the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The entity to use for fetching the component.
         * @param outComponent The output result for the fetched component, if there is one.
         *
         * @return true if a component was found and returned in outComponent.
         * @return false if no component exists.
         */
        [[nodiscard]] bool TryGetComponent(EntityId entity, TComponent& outComponent) const noexcept
        {
            // TODO: This sucks. - Matt J.
            EntityHandle handle{};

            try
            {
                handle = _entityAllocator->CreateHandleForAllocated(entity);
            }
            catch (...)
            {
                return false;
            }

            return TryGetComponent(handle, outComponent);
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
         *
         */
        [[nodiscard]] bool TryGetComponent(const EntityHandle& entity, TComponent& outComponent) const noexcept
        {
            return _entityAllocator->IsValid(entity) && _componentBuffer.TryGetComponent(entity.Id, outComponent);
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
         *
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        [[nodiscard]] TComponent GetComponentUnsafe(EntityId entity) const
        {
            return GetComponentUnsafe(_entityAllocator->CreateHandleForAllocated(entity));
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method. This is considered an unsafe operation. Before calling this, you must guarantee that the
         * provided entity exists in the read-only portion of the underlying buffer. Please see
         * ComponentView::HasComponent for more information.
         *
         * @param entity The EntityHandle& to retrieve the component from.
         *
         * @return A copy of the current state of the component of type TComponent attached to the given entity.
         *
         * @exception Exceptions::KeyNotFoundException if the ID is not currently allocated by this ECS instance.
         * @exception std::bad_alloc if memory fails to be allocated as part of this operation.
         */
        [[nodiscard]] TComponent GetComponentUnsafe(const EntityHandle& entity) const
        {
            if (!_entityAllocator->IsValid(entity))
            {
                throw Exceptions::KeyNotFoundException();
            }

            return _componentBuffer.GetComponentUnsafe(entity.Id);
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
