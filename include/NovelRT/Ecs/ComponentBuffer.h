// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTBUFFER_H
#define NOVELRT_ECS_COMPONENTBUFFER_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A storage type that manages the storage and modification of the given type concurrently. You should not be
     * instantiating this yourself in a regular setup.
     *
     * Please note that this storage type assumes that the component in question is a simple struct at all times.
     * You should not have component types that are massively complex as there may be many copy instructions that are
     * not SIMDifiable if the type is too complicated. The type T of the ComponentBuffer must be trivially copyable as
     * defined by the C++ language reference. This is due to the internal language binding mechanisms of NovelRT, and is
     * enforced by a check against std::is_trivally_copyable. The type in question will need to have addition and an
     * equality comparison operator implemented in order for it to function as a type a ComponentBuffer can manage for
     * you.
     *
     * @tparam T The type of component this ComponentBuffer will manage.
     */
    template<typename T> class ComponentBuffer
    {
    private:
        std::shared_ptr<ComponentBufferMemoryContainer> _innerContainer;

    public:
        /**
         * @brief Constructs a new ComponentBuffer for type T. In a regular ECS setup, you should not be instantiating
         * this yourself.
         *
         *
         * @param poolSize The amount of worker threads being utilised in this instance of the ECS.
         * @param serialisedTypeName The type name to use for serialisation of this data type.
         * @param deleteInstructionState The component state to treat as the delete instruction. When this state is
         * passed in during an update, the ComponentBuffer will delete the component from the target entity during
         * resolution.
         */
        ComponentBuffer(size_t poolSize, T deleteInstructionState, const std::string& serialisedTypeName) noexcept
            : _innerContainer(std::make_shared<ComponentBufferMemoryContainer>(
                  poolSize,
                  &deleteInstructionState,
                  sizeof(T),
                  [](auto rootComponent, auto updateComponent, auto)
                  { *reinterpret_cast<T*>(rootComponent) += *reinterpret_cast<const T*>(updateComponent); },
                  [](const void* left, const void* right)
                  { return *reinterpret_cast<const T*>(left) == *reinterpret_cast<const T*>(right); },
                  serialisedTypeName))
        {
            static_assert(std::is_trivially_copyable<T>::value,
                          "Value type must be trivially copyable for use with a ComponentBuffer. See the documentation "
                          "for more information.");
        }

        /**
         * @brief Creates a new ComponentBuffer with an existing ComponentBufferMemoryContainer as the underlying memory
         * store. In a regular ECS setup, you should not be instantiating this yourself.
         *
         * This is an unsafe operation. Memory containers do not persist any form of type safety.
         * Please ensure that type T is either the same as, or is compatible with, the underlying data.
         * If a container is supplied that does not match type T then the behaviour of the entire object is undefined.
         *
         * @param innerContainer The container to base this ComponentBuffer on.
         */
        explicit ComponentBuffer(std::shared_ptr<ComponentBufferMemoryContainer> innerContainer) noexcept
            : _innerContainer(std::move(innerContainer))
        {
        }

        /**
         * @brief Fetches the underlying ComponentBufferMemoryContainer associated with this ComponentBuffer instance.
         *
         * Accessing the underlying memory container is considered an unsafe operation. In a regular ECS scenario, you
         * should not need to access it. This is a pure method. Calling this without using the result has no effect and
         * introduces the overhead for calling a method.
         *
         * @return The underlying container.
         */
        [[nodiscard]] std::shared_ptr<ComponentBufferMemoryContainer> GetUnderlyingContainer() const noexcept
        {
            return _innerContainer;
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
            _innerContainer->PrepContainerForFrame(destroyedEntities);
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
            return *reinterpret_cast<const T*>(_innerContainer->GetDeleteInstructionState().GetDataHandle());
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
         * @exception std::out_of_range if an invalid poolId is provided.
         */
        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, T component)
        {
            _innerContainer->PushComponentUpdateInstruction(poolId, entity, &component);
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The entity to use for fetching the component.
         * @return A copy of the current state of the component of type T attached to the given entity.
         * @exception Exceptions::KeyNotFoundException if the given EntityId is not present within the set.
         */
        [[nodiscard]] T GetComponent(EntityId entity) const
        {
            return *reinterpret_cast<const T*>(_innerContainer->GetComponent(entity).GetDataHandle());
        }

        /**
         * @brief Attempts to get the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param entity The entity to use for fetching the component.
         * @return optional T result, if the fetch failed the optional will not have a value.
         */
        [[nodiscard]] std::optional<T> TryGetComponent(EntityId entity) const noexcept
        {
            if (!HasComponent(entity))
            {
                return std::optional<T>{};
            }

            return GetComponentUnsafe(entity);
        }

        /**
         * @brief Gets a copy of the component instance attached to this entity.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method. This is considered an unsafe operation. Before calling this, you must guarantee that the
         * provided entity exists in the read-only portion of the underlying buffer. Please see
         * ComponentBuffer::HasComponent for more information.
         *
         * @param entity The entity to use for fetching the component.
         * @return A copy of the current state of the component of type T attached to the given entity.
         */
        [[nodiscard]] T GetComponentUnsafe(EntityId entity) const noexcept
        {
            return *reinterpret_cast<const T*>(_innerContainer->GetComponentUnsafe(entity).GetDataHandle());
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
            return _innerContainer->HasComponent(entity);
        }

        /**
         * @brief Gets the serialised type name used for the loading and unloading to and from serialised data.
         *
         * @return The serialised type name as a string.
         */
        [[nodiscard]] const std::string& GetSerialisedTypeName() const noexcept
        {
            return _innerContainer->GetSerialisedTypeName();
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
            return _innerContainer->GetImmutableDataLength();
        }

        /**
         * @brief Gets the beginning forward const iterator state for the immutable data in this ComponentBuffer.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] typename SparseSet<EntityId, T>::ConstIterator begin() const noexcept
        {
            return typename SparseSet<EntityId, T>::ConstIterator(_innerContainer->begin());
        }

        /**
         * @brief Gets the end forward const iterator state for the immutable data in this ComponentBuffer.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] typename SparseSet<EntityId, T>::ConstIterator end() const noexcept
        {
            return typename SparseSet<EntityId, T>::ConstIterator(_innerContainer->end());
        }
    };
}

#endif //! NOVELRT_ECS_COMPONENTBUFFER_H
