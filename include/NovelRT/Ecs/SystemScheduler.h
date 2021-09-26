// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_SYSTEMSCHEDULER_H
#define NOVELRT_ECS_SYSTEMSCHEDULER_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief Handles all thread and system scheduling related tasks. In a normal ECS instance, this is your root
     * object.
     *
     */
    class SystemScheduler
    {
    private:
        struct QueueLockPair
        {
            std::optional<Atom> systemUpdateId;
            std::mutex threadLock;
        };

        std::vector<Atom> _systemIds;

        static inline const uint32_t DEFAULT_BLIND_THREAD_LIMIT = 8;

        std::unordered_map<Atom, std::function<void(Timing::Timestamp, Catalogue)>, AtomHashFunction> _systems;

        EntityCache _entityCache;
        ComponentCache _componentCache;

        uint32_t _workerThreadCount;

        std::vector<QueueLockPair> _threadWorkQueues;
        std::vector<std::thread> _threadCache;

        Timing::Timestamp _currentDelta;
        std::atomic_uint64_t _threadAvailabilityMap;

        std::atomic_bool _shouldShutDown;

        bool JobAvailable(size_t poolId) noexcept;
        void CycleForJob(size_t poolId);
        void ScheduleUpdateWork(std::queue<Atom>& systemIds);

    public:
        /**
         * @brief Constructs a new instance of SystemScheduler.
         *
         * @param maximumThreadCount An optional parameter should the developer know in advance how many threads they
         * wish to dedicate to this SystemScheduler.
         */
        explicit SystemScheduler(uint32_t maximumThreadCount = 0) noexcept;

        /**
         * @brief Registers a function to the SystemScheduler instance.
         *
         * @param systemUpdatePtr a valid std::function object that points to the system function in question.
         */
        void RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr) noexcept;

        /**
         * @brief Gets the amount of worker threads associated with this SystemScheduler.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return uint32_t The total count of worker threads.
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
         * @return EntityCache& A mutable reference to the EntityCache instance associated with this SystemScheduler.
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
         * @return const EntityCache& A const reference to the EntityCache instance associated with this
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
         * @return ComponentCache& A mutable reference to the ComponentCache instance associated with this
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
         * @return const ComponentCache& A const reference to the ComponentCache instance associated with this
         * SystemScheduler.
         */
        [[nodiscard]] inline const ComponentCache& GetComponentCache() const noexcept
        {
            return _componentCache;
        }

        /**
         * @brief Initialises the allocated worker threads for ECS processing.
         *
         * This only needs to be called once, and should not be called by the developer in a standard ECS instance.
         *
         */
        void SpinThreads() noexcept;

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
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_SYSTEMSCHEDULER_H
