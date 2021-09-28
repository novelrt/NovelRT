// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    SystemScheduler::SystemScheduler(uint32_t maximumThreadCount) noexcept
        : _entityCache(1),
          _componentCache(1),
          _workerThreadCount(maximumThreadCount),
          _currentDelta(0),
          _threadAvailabilityMap(0),
          _shouldShutDown(false),
          _threadsAreSpinning(false)
    {
        if (_workerThreadCount == 0)
        {
            _workerThreadCount = std::thread::hardware_concurrency() - 1;
        }

        if (_workerThreadCount == 0)
        {
            _workerThreadCount = DEFAULT_BLIND_THREAD_LIMIT;
        }

        // in case the previous call doesn't work

        _entityCache = EntityCache(_workerThreadCount);
        _componentCache = ComponentCache(_workerThreadCount);
    }

    SystemScheduler::SystemScheduler(SystemScheduler&& other) noexcept
        : _systemIds(std::move(other._systemIds)),
          _systems(std::move(other._systems)),
          _entityCache(std::move(other._entityCache)),
          _componentCache(std::move(other._componentCache)),
          _workerThreadCount(other._workerThreadCount),
          _currentDelta(other._currentDelta),
          _threadAvailabilityMap(0),
          _shouldShutDown(false),
          _threadsAreSpinning(false)
    {
        if (other.GetThreadsAreSpinning())
        {
            other.ShutDown();
            SpinThreads();
        }
    }

    SystemScheduler& SystemScheduler::operator=(SystemScheduler&& other) noexcept
    {
        _systemIds = std::move(other._systemIds);
        _systems = std::move(other._systems);
        _entityCache = std::move(other._entityCache);
        _componentCache = std::move(other._componentCache);
        _workerThreadCount = other._workerThreadCount;
        _threadWorkQueues = std::move(other._threadWorkQueues);
        _threadCache = std::move(other._threadCache);
        _currentDelta = other._currentDelta;
        _shouldShutDown = false;
        _threadsAreSpinning = false;

        if (other.GetThreadsAreSpinning())
        {
            other.ShutDown();
            SpinThreads();
        }

        return *this;
    }

    void SystemScheduler::RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr) noexcept
    {
        Atom id = Atom::getNextSystemId();
        _systems.emplace(id, systemUpdatePtr);
        _systemIds.emplace_back(id);
    }

    bool SystemScheduler::JobAvailable(size_t poolId) noexcept
    {
        QueueLockPair& pair = _threadWorkQueues[poolId];
        pair.threadLock.lock();

        if (pair.systemUpdateId.has_value())
        {
            return true;
        }
        pair.threadLock.unlock();

        return false;
    }

    void SystemScheduler::CycleForJob(size_t poolId)
    {
        while (true)
        {
            while (!JobAvailable(poolId))
            {
                if (_shouldShutDown)
                {
                    if ((_threadAvailabilityMap & 1ULL << poolId) != 0)
                    {
                        _threadAvailabilityMap ^= 1ULL << poolId;
                    }
                    return;
                }

                if ((_threadAvailabilityMap & 1ULL << poolId) != 0)
                {
                    _threadAvailabilityMap ^= 1ULL << poolId;
                }

                std::this_thread::yield();
            }

            QueueLockPair& pair = _threadWorkQueues[poolId];

            Atom workItem = pair.systemUpdateId.value();

            pair.systemUpdateId.reset();
            pair.threadLock.unlock();

            _systems[workItem](_currentDelta, Catalogue(poolId, _componentCache, _entityCache));
        }
    }

    void SystemScheduler::ScheduleUpdateWork(std::queue<Atom>& systemIds)
    {
        while (!systemIds.empty())
        {
            for (size_t workerIndex = 0; workerIndex < _threadWorkQueues.size(); workerIndex++)
            {
                auto& pair = _threadWorkQueues[workerIndex];

                if (systemIds.empty())
                {
                    break;
                }

                const std::lock_guard<std::mutex> lock(pair.threadLock);

                if (pair.systemUpdateId.has_value())
                {
                    continue;
                }

                pair.systemUpdateId = systemIds.front();
                systemIds.pop();

                if ((_threadAvailabilityMap & 1ULL << workerIndex) == 0)
                {
                    _threadAvailabilityMap ^= 1ULL << workerIndex;
                }
            }

            std::this_thread::yield();
        }

        while (_threadAvailabilityMap != 0)
        {
            std::this_thread::yield();
        }
    }

    void SystemScheduler::SpinThreads() noexcept
    {
        _shouldShutDown = false;
        std::vector<QueueLockPair> vec2(_workerThreadCount);
        _threadWorkQueues.swap(vec2);

        for (size_t i = 0; i < _workerThreadCount; i++)
        {
            _threadCache.emplace_back(std::thread([&, i]() { CycleForJob(i); }));
        }

        _threadsAreSpinning = true;
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {

        _currentDelta = delta;

        std::queue<Atom> workQueue;

        for (Atom id : _systemIds)
        {
            workQueue.push(id);
        }

        ScheduleUpdateWork(workQueue);
        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());

        _entityCache.ProcessEntityDeletionRequestsFromThreads();
    }

    void SystemScheduler::ShutDown() noexcept
    {
        _shouldShutDown = true;

        for (size_t i = 0; i < _threadCache.size(); i++)
        {
            if (_threadCache[i].joinable())
            {
                _threadCache[i].join();
            }
        }

        _threadCache.clear();
        _threadWorkQueues.clear();
        _threadsAreSpinning = false;
    }

    SystemScheduler::~SystemScheduler() noexcept
    {
        if (GetThreadsAreSpinning())
        {
            ShutDown();
        }
    }
} // namespace NovelRT::Ecs
