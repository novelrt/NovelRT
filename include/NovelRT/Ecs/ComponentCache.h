// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include "../Exceptions/OutOfMemoryException.h"
#include "../Utilities/Event.h"
#include "ComponentBuffer.h"
#include "EcsUtils.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace NovelRT::Ecs
{
    /**
     * @brief Stores all ComponentBuffer instances currently initialised for this instance of the ECS. You should not be
     * instantiating this yourself in a regular setup.
     *
     */
    class ComponentCache
    {
    private:
        std::unordered_map<ComponentTypeId, std::shared_ptr<ComponentBufferMemoryContainer>, AtomHashFunction>
            _componentMap;
        size_t _poolSize;
        Utilities::Event<const std::vector<EntityId>&> _bufferPrepEvent;

        std::shared_ptr<ComponentBufferMemoryContainer> CreateContainer(
            size_t sizeOfDataType,
            void* deleteInstructionState,
            const std::function<void(SparseSetMemoryContainer::ByteIteratorView,
                                     SparseSetMemoryContainer::ByteIteratorView,
                                     size_t)>& componentUpdateLogic) const;

    public:
        /**
         * @brief Constructs a new ComponentCache with a given thread pool size.
         *
         * @param poolSize The amount of worker threads to allocate for.
         */
        explicit ComponentCache(size_t poolSize) noexcept;

        /**
         * @brief Registers a new component type and stores it internally.
         *
         * This is considered an unsafe operation. If the data stored in deleteInstructionState does not match with the
         * specified size, or if the type being used is not trivially copyable as defined by the C++ language reference,
         * then the behaviour is undefined. See ComponentBuffer and std::is_trivially_copyable for more information.
         *
         * The returned ID cannot be discarded. If the value is discarded, then the container is lost permanently.
         *
         * @param sizeOfDataType The size of the object type, in bytes.
         * @param deleteInstructionState The object state that indicates that the component should be deleted.
         * @return ComponentTypeId the ID of the new component type and associated ComponentBufferMemoryContainer
         * instance.
         *
         * @exception std::bad_alloc when a ComponentBuffer could not be allocated in memory for the given component
         * type.
         */
        [[nodiscard]] ComponentTypeId RegisterComponentTypeUnsafe(
            size_t sizeOfDataType,
            void* deleteInstructionState,
            std::function<void(SparseSetMemoryContainer::ByteIteratorView,
                               SparseSetMemoryContainer::ByteIteratorView,
                               size_t)> componentUpdateLogic);

        /**
         * @brief Registers a new component type to the cache.
         *
         * This method allocates a new ComponentBuffer instance for T and stores it internally.
         * This method is not thread safe. as a result, all components should be registered before any iterations of the
         * ECS are performed. If this is executed concurrently, it is highly likely you will end up with a segfault.
         *
         * @tparam T The component type to register.
         * @param deleteInstructionState The instruction state for the component used for recognising a delete
         * instruction.
         *
         * @exception std::bad_alloc when a ComponentBuffer could not be allocated in memory for the given component
         * type.
         */
        template<typename T> void RegisterComponentType(T deleteInstructionState)
        {
            std::shared_ptr<ComponentBufferMemoryContainer> ptr =
                CreateContainer(sizeof(T), &deleteInstructionState, [](auto rootComponent, auto updateComponent, auto) {
                    *reinterpret_cast<T*>(rootComponent.GetDataHandle()) +=
                        *reinterpret_cast<T*>(updateComponent.GetDataHandle());
                });
            _bufferPrepEvent += [ptr](auto vec) { ptr->PrepContainerForFrame(vec); };
            _componentMap.emplace(GetComponentTypeId<T>(), ptr);
        }

        /**
         * @brief Get the ComponentBuffer instance that manages the specified component type.
         *
         * This is a pure method. Retrieving the ComponentBuffer and then discarding it has no effect and introduces the
         * overhead of a method call.
         *
         * @tparam T The component type that the returned ComponentBuffer manages.
         * @return ComponentBuffer<T> The ComponentBuffer for T by reference.
         *
         * @exceptions std::out_of_range if the specified component type has not been registered.
         */
        template<typename T>[[nodiscard]] ComponentBuffer<T> GetComponentBuffer()
        {
            return ComponentBuffer<T>(_componentMap.at(GetComponentTypeId<T>()));
        }

        /**
         * @brief Prepares all ComponentBuffer instances for the next update cycle.
         *
         * This method is not thread safe. It should also not be explicitly called by the end user in a regular ECS
         * setup.
         *
         * @param entitiesToDelete All entities that were explicitly pushed for deletion in the last update cycle.
         */
        void PrepAllBuffersForNextFrame(const std::vector<EntityId>& entitiesToDelete) noexcept;
    };
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_COMPONENTCACHE_H