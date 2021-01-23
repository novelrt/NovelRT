// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTCACHE_H
#define NOVELRT_ECS_COMPONENTCACHE_H

#include "../Exceptions/OutOfMemoryException.h"
#include "../Utilities/Event.h"
#include "ComponentBuffer.h"
#include "EcsUtils.h"
#include <functional>
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
        std::unordered_map<ComponentTypeId, void*, AtomHashFunction> _componentMap;
        std::vector<std::function<void()>> _destructorFunctions;
        size_t _poolSize;
        Utilities::Event<const std::vector<EntityId>&> _bufferPrepEvent;

    public:
        /**
         * @brief Constructs a new ComponentCache with a given thread pool size.
         *
         * @param poolSize The amount of worker threads to allocate for.
         */
        ComponentCache(size_t poolSize) noexcept;

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
         * @exception Exceptions::OutOfMemoryException when a ComponentBuffer could not be allocated in memory for the
         * given component type.
         */
        template<typename T> void RegisterComponentType(T deleteInstructionState)
        {
            auto ptr = malloc(sizeof(ComponentBuffer<T>));

            if (ptr == nullptr)
            {
                throw Exceptions::OutOfMemoryException(
                    "Could not allocate component buffer for new component registration.");
            }
            auto bufferPtr = new (ptr) ComponentBuffer<T>(_poolSize, deleteInstructionState);
            _destructorFunctions.push_back([bufferPtr]() { bufferPtr->~ComponentBuffer<T>(); });
            _bufferPrepEvent += [bufferPtr](auto arg) { bufferPtr->PrepComponentBufferForFrame(arg); };
            _componentMap.emplace(GetComponentTypeId<T>(), ptr);
        }

        /**
         * @brief Get the ComponentBuffer instance that manages the specified component type.
         *
         * This is a pure method. Retrieving the ComponentBuffer and then discarding it has no effect and introduces the
         * overhead of a method call.
         *
         * @tparam T The component type that the returned ComponentBuffer manages.
         * @return ComponentBuffer<T>& The ComponentBuffer for T by reference.
         */
        template<typename T>[[nodiscard]] ComponentBuffer<T>& GetComponentBuffer() noexcept
        {
            return *reinterpret_cast<ComponentBuffer<T>*>(_componentMap.at(GetComponentTypeId<T>()));
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

        ~ComponentCache() noexcept;
    };
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_COMPONENTCACHE_H