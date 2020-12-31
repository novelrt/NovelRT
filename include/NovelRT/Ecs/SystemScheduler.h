// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_SYSTEMSCHEDULER_H
#define NOVELRT_ECS_SYSTEMSCHEDULER_H

#include "../Timing/Timestamp.h"
#include "Catalogue.h"
#include "ComponentCache.h"
#include "EcsUtils.h"
#include "EntityCache.h"
#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

namespace NovelRT::Ecs
{
    class SystemScheduler
    {
      private:
        struct QueueLockPair
        {
            std::vector<Atom> systemUpdateIds;
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
        std::atomic_uint64_t _threadShutDownStatus;
        std::atomic_bool _shouldShutDown;

        std::atomic_size_t _ecsDataBufferIndex;

        bool JobAvailable(size_t poolId) noexcept;
        void CycleForJob(size_t poolId);
        void ScheduleUpdateWork(size_t workersToAssign, size_t amountOfWork);

      public:
        SystemScheduler(uint32_t maximumThreadCount = 0) noexcept;

        void RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr) noexcept;

        [[nodiscard]] inline uint32_t GetWorkerThreadCount() const noexcept
        {
            return _workerThreadCount;
        }

        [[nodiscard]] inline EntityCache& GetEntityCache() noexcept
        {
            return _entityCache;
        }

        [[nodiscard]] inline const EntityCache& GetEntityCache() const noexcept
        {
            return _entityCache;
        }

        [[nodiscard]] inline ComponentCache& GetComponentCache() noexcept
        {
            return _componentCache;
        }

        [[nodiscard]] inline const ComponentCache& GetComponentCache() const noexcept
        {
            return _componentCache;
        }

        void SpinThreads() noexcept;

        void ExecuteIteration(Timing::Timestamp delta);

        ~SystemScheduler() noexcept;
    };
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_SYSTEMSCHEDULER_H