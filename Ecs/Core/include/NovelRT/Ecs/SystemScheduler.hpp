#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>
#include <NovelRT/Timing/Timestamp.hpp>
#include <NovelRT/Utilities/Atom.hpp>

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>

#include <oneapi/tbb/mutex.h>
#include <oneapi/tbb/task_arena.h>
#include <oneapi/tbb/task_group.h>

namespace NovelRT::Ecs
{
    class Catalogue;
    class ComponentCache;
    class EntityCache;
    class IEcsSystem;

    /**
     * @brief Handles all thread and system scheduling related tasks. In a normal ECS instance, this is your root
     * object.
     *
     */
    class SystemScheduler
    {
    private:
        std::vector<Atom> _systemIds;

        static constexpr uint32_t DefaultBlindThreadLimit = 8;

        std::vector<std::shared_ptr<IEcsSystem>> _typedSystemCache;
        std::unordered_map<Atom, std::function<void(Timing::Timestamp, Catalogue)>> _systems;

        EntityCache _entityCache;
        ComponentCache _componentCache;

        uint32_t _workerThreadCount;

        std::unique_ptr<tbb::task_arena> _ecsArena;
        std::unique_ptr<tbb::task_arena> _asyncArena;
        std::unique_ptr<tbb::task_group> _ecsTasks;
        std::unique_ptr<tbb::task_group> _asyncTasks;

        Timing::Timestamp _currentDelta;

        std::atomic_bool _shouldShutDown;
        bool _threadsAreSpinning;

        void ScheduleUpdateWork();

    public:
        /**
         * @brief Constructs a new instance of SystemScheduler.
         *
         * @param maximumThreadCount An optional parameter should the developer know in advance how many threads they
         * wish to dedicate to this SystemScheduler.
         */
        explicit SystemScheduler(uint32_t maximumThreadCount = 0) noexcept;

        SystemScheduler(const SystemScheduler& other) = delete;
        SystemScheduler& operator=(const SystemScheduler& other) = delete;

        /**
         * @brief Move constructor for moving instances of SystemScheduler.
         *
         * @param other The move target.
         */
        SystemScheduler(SystemScheduler&& other) noexcept;

        /**
         * @brief Move assignment operator for move assigning instances of SystemScheduler.
         *
         * @param other The move target.
         * @return The moved instance of SystemScheduler.
         */
        SystemScheduler& operator=(SystemScheduler&& other) noexcept;

        /**
         * @brief Registers a function to the SystemScheduler instance.
         *
         * @param systemUpdatePtr a valid std::function object that points to the system function in question.
         */
        void RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr) noexcept;

        /**
         * @brief Registers an IEcsSystem instance to the SystemScheduler instance.
         *
         * @param targetSystem a valid std::function object that points to the system function in question.
         */
        void RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem) noexcept;

        /**
         * @brief Gets the amount of worker threads associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The total count of worker threads.
         */
        [[nodiscard]] inline uint32_t GetWorkerThreadCount() const noexcept
        {
            return _workerThreadCount;
        }

        /**
         * @brief Gets a mutable reference to the EntityCache instance associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return A mutable reference to the EntityCache instance associated with this SystemScheduler.
         */
        [[nodiscard]] inline EntityCache& GetEntityCache() noexcept
        {
            return _entityCache;
        }

        /**
         * @brief Gets a const reference to the EntityCache instance associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return A const reference to the EntityCache instance associated with this
         * SystemScheduler.
         */
        [[nodiscard]] inline const EntityCache& GetEntityCache() const noexcept
        {
            return _entityCache;
        }

        /**
         * @brief Gets a mutable reference to the ComponentCache instance associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return A mutable reference to the ComponentCache instance associated with this
         * SystemScheduler.
         */
        [[nodiscard]] inline ComponentCache& GetComponentCache() noexcept
        {
            return _componentCache;
        }

        /**
         * @brief Gets a const reference to the ComponentCache instance associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return A const reference to the ComponentCache instance associated with this
         * SystemScheduler.
         */
        [[nodiscard]] inline const ComponentCache& GetComponentCache() const noexcept
        {
            return _componentCache;
        }

        /**
         * @brief Searches for a registered instance of a system of the specified type. Only works with IEcsSystem
         * implementations.
         *
         * @tparam TSystemType The type of IEcsSystem to search for.
         * @return A shared pointer to a system of the specified type.
         *
         * @exception Exceptions::KeyNotFoundException if the specified type does not have a registered instance.
         */
        template<typename TSystemType>
        [[nodiscard]] std::shared_ptr<TSystemType> GetRegisteredIEcsSystemAs() const
        {
            std::shared_ptr<TSystemType> returnPtr = nullptr;

            for (auto&& ptr : _typedSystemCache)
            {
                returnPtr = std::dynamic_pointer_cast<TSystemType>(ptr);

                if (returnPtr != nullptr)
                {
                    break;
                }
            }

            if (returnPtr == nullptr)
            {
                throw Exceptions::KeyNotFoundException();
            }

            return returnPtr;
        }

        /**
         * @brief Executes an iteration of the ECS.
         *
         * @param delta the current delta time to supply to systems.
         *
         * @exception Any and all exceptions that might possibly propagate from any given system.
         */
        void ExecuteIteration(Timing::Timestamp delta);

        /**
         * @brief Destroys the SystemScheduler.
         *
         * The destructor also implicitly shuts down all threads being used by this scheduler.
         *
         */
        ~SystemScheduler() noexcept;
    };
}
