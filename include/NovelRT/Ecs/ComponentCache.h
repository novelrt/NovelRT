// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

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
            const void* deleteInstructionState,
            const std::function<void(void*, const void*, size_t)>& componentUpdateLogic,
            const std::string& serialisedTypeName) const;

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
         * The returned ID cannot be discarded. If the value is discarded, then the container is lost permanently,
         * effectively causing a memory leak.
         *
         * @param sizeOfDataType The size of the object type, in bytes.
         * @param deleteInstructionState The object state that indicates that the component should be deleted.
         * @param componentUpdateLogic The function to use for concurrent update consolidation.
         * @param serialisedTypeName The type name to use for data serialisation.
         * @return the ID of the new component type and associated ComponentBufferMemoryContainer
         * instance.
         *
         * @exception std::bad_alloc when a ComponentBuffer could not be allocated in memory for the given component
         * type.
         */
        [[nodiscard]] ComponentTypeId RegisterComponentTypeUnsafe(
            size_t sizeOfDataType,
            const void* deleteInstructionState,
            const std::function<void(void*, const void*, size_t)>& componentUpdateLogic,
            const std::string& serialisedTypeName);

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
        template<typename T> void RegisterComponentType(T deleteInstructionState, const std::string& serialisedTypeName)
        {
            std::shared_ptr<ComponentBufferMemoryContainer> ptr =
                CreateContainer(sizeof(T), &deleteInstructionState, [](auto rootComponent, auto updateComponent, auto) {
                    *reinterpret_cast<T*>(rootComponent) += *reinterpret_cast<const T*>(updateComponent);
                }, serialisedTypeName);
            _bufferPrepEvent += [ptr](auto vec) { ptr->PrepContainerForFrame(vec); };
            _componentMap.emplace(GetComponentTypeId<T>(), ptr);
        }

        /**
         * @brief Returns a pointer to the memory container associated with this ID without type information.
         *
         * TODO: docs
         *
         * @param id
         * @return
         */
        [[nodiscard]] std::shared_ptr<ComponentBufferMemoryContainer> GetComponentBufferById(ComponentTypeId id) const;

        /**
         * @brief Get the ComponentBuffer instance that manages the specified component type.
         *
         * This is a pure method. Retrieving the ComponentBuffer and then discarding it has no effect and introduces the
         * overhead of a method call.
         *
         * @tparam T The component type that the returned ComponentBuffer manages.
         * @return The ComponentBuffer for type T mapped to the correct memory container.
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
}

#endif //! NOVELRT_ECS_COMPONENTCACHE_H