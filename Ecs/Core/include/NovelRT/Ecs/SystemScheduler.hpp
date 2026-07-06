#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/ImplDetail.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>
#include <NovelRT/Timing/Timestamp.hpp>

#include <atomic>
#include <functional>
#include <memory>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <oneapi/tbb/concurrent_queue.h>
#include <oneapi/tbb/concurrent_unordered_map.h>
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
        friend class Catalogue;

    private:
        struct SystemJobInfo
        {
            std::function<bool(Timing::Timestamp, Catalogue)> jobFnPtr;
            std::atomic_bool isDone{false};

            explicit SystemJobInfo(std::function<bool(Timing::Timestamp, Catalogue)> job) noexcept
                : jobFnPtr(std::move(job))
            {
            }
        };

        std::vector<SystemId> _systemIds;

        static constexpr uint32_t DefaultBlindThreadLimit = 8;

        std::vector<std::shared_ptr<IEcsSystem>> _typedSystemCache;
        std::unordered_map<SystemId, std::function<void(Timing::Timestamp, Catalogue)>> _systems;
        std::unordered_map<SystemId, std::vector<SystemId>> _systemDependencies;
        std::vector<std::vector<SystemId>> _schedulingLayers;
        std::unordered_set<SystemId> _terminalSystemIds;

        EntityCache _entityCache;
        ComponentCache _componentCache;

        uint32_t _workerThreadCount;

        std::unique_ptr<tbb::task_arena> _ecsArena;
        std::unique_ptr<tbb::task_arena> _asyncArena;
        std::unique_ptr<tbb::task_group> _ecsTasks;
        std::unique_ptr<tbb::task_group> _asyncTasks;
        tbb::concurrent_queue<std::function<void(Timing::Timestamp, Catalogue)>> _pendingCompletions;
        tbb::concurrent_unordered_map<SystemId, SystemJobInfo> _systemJobs;
        tbb::concurrent_queue<SystemId> _jobCancellations;

        Timing::Timestamp _currentDelta;

        bool _hasExecutedAtLeastOnce;

        void ScheduleUpdateWork();

        template<typename TWork, typename TCompletion>
        requires Detail::ValidScheduleWithCompletion<TWork, TCompletion> void ScheduleWithCompletion(
            TWork&& work,
            TCompletion&& completion) noexcept;

        SystemId ScheduleSystemJob(std::function<bool(Timing::Timestamp, Catalogue)> jobFnPtr);
        void CancelSystemJob(SystemId jobId);

        void RebuildSystemDependencyTreeLayers();

        [[nodiscard]] SystemId RegisterSystemInternalNoTreeRebuild(
            std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr,
            std::span<const SystemId> dependencies);

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
         * @warning Registering the same function twice results in undefined behaviour. Unlike IEcsSystem registrations,
         * duplicate function registrations cannot be detected at runtime. It is the caller's responsibility to ensure
         * each system function is only registered once.
         *
         * @param systemUpdatePtr a valid std::function object that points to the system function in question.
         * @param dependencies a collection of system IDs used to signal to the scheduler when to run this system in a
         * given iteration.
         * @return The internal ID of the registered system.
         *
         * @exception std::invalid_argument if any of the provided dependency IDs do not match a registered system.
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr,
                                              std::span<const SystemId> dependencies);

        /**
         * @brief Registers a function to the SystemScheduler instance with no dependencies.
         *
         * @warning Registering the same function twice results in undefined behaviour. Unlike IEcsSystem registrations,
         * duplicate function registrations cannot be detected at runtime. It is the caller's responsibility to ensure
         * each system function is only registered once.
         *
         * @param systemUpdatePtr a valid std::function object that points to the system function in question.
         * @return The internal ID of the registered system.
         *
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr);

        /**
         * @brief Registers an IEcsSystem instance to the SystemScheduler instance.
         *
         * @param targetSystem a valid IEcsSystem object instance.
         * @param dependencies a collection of system IDs used to signal to the scheduler when to run this system in a
         * given iteration.
         * @return The internal ID of the registered system.
         *
         * @exception std::invalid_argument if the provided system has already been registered, or if any of the
         * provided dependency IDs do not match a registered system.
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem,
                                              std::span<const SystemId> dependencies);

        /**
         * @brief Registers an IEcsSystem instance to the SystemScheduler instance with no dependencies.
         *
         * @param targetSystem a valid IEcsSystem object instance.
         * @return The internal ID of the registered system.
         *
         * @exception std::invalid_argument if the provided system has already been registered.
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem);

        /**
         * @brief Registers a function to the SystemScheduler instance as a terminal system. A terminal system depends
         * on all other non-terminal systems and is always scheduled in the final layer of execution.
         *
         * @warning Registering the same function twice results in undefined behaviour. Unlike IEcsSystem registrations,
         * duplicate function registrations cannot be detected at runtime. It is the caller's responsibility to ensure
         * each system function is only registered once.
         *
         * @param systemUpdatePtr a valid std::function object that points to the system function in question.
         * @return The internal ID of the registered system.
         *
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystemDependsOnAll(
            std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr);

        /**
         * @brief Registers an IEcsSystem instance to the SystemScheduler instance as a terminal system. A terminal
         * system depends on all other non-terminal systems and is always scheduled in the final layer of execution.
         *
         * @param targetSystem a valid IEcsSystem object instance.
         * @return The internal ID of the registered system.
         *
         * @exception std::invalid_argument if the provided system has already been registered.
         * @exception Exceptions::InvalidOperationException if this method is called after the first iteration has been
         * executed.
         */
        [[nodiscard]] SystemId RegisterSystemDependsOnAll(std::shared_ptr<IEcsSystem> targetSystem);

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
         * The destructor waits for any in-flight ECS and async tasks to complete
         * before releasing all resources.
         *
         */
        ~SystemScheduler() noexcept;
    };
}

#include <NovelRT/Ecs/MiscTemplateImpls.hpp> // This has to be here due to template implementation details - Matt J.
