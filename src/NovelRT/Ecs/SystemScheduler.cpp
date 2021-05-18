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
          _threadShutDownStatus(0),
          _shouldShutDown(false),
          _ecsDataBufferIndex(0)
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
        if (pair.systemUpdateIds.size() > 0)
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
                    _threadShutDownStatus ^= 1ULL << poolId;
                    return;
                }

                if ((_threadAvailabilityMap & 1ULL << poolId) != 0)
                {
                    _threadAvailabilityMap ^= 1ULL << poolId;
                }

                std::this_thread::yield();
            }

            bool firstIteration = true;

            while (true)
            {
                QueueLockPair& pair = _threadWorkQueues[poolId];
                if (!firstIteration)
                {
                    pair.threadLock.lock();
                }
                else
                {
                    firstIteration = false;
                }

                if (pair.systemUpdateIds.size() == 0)
                {
                    pair.threadLock.unlock();
                    break;
                }

                Atom workItem = pair.systemUpdateIds[0];
                pair.systemUpdateIds.erase(pair.systemUpdateIds.begin());

                pair.threadLock.unlock();

                _systems[workItem](_currentDelta, Catalogue(poolId, _componentCache, _entityCache));
            }
            _threadAvailabilityMap ^= 1ULL << poolId;
        }
    }

    void SystemScheduler::ScheduleUpdateWork(size_t workersToAssign, size_t amountOfWork)
    {
        if (_systemIds.empty())
        {
            return;
        }

        int32_t sizeOfProcessedWork = 0;

        for (size_t i = 0; i < workersToAssign; i++)
        {
            size_t offset = i * amountOfWork;
            QueueLockPair& pair = _threadWorkQueues[i];


            pair.threadLock.lock();

            _threadAvailabilityMap ^= 1ULL << i;
            for (size_t j = 0; j < amountOfWork; j++)
            {
                size_t currentWorkIndex = offset + j;
                pair.systemUpdateIds.push_back(_systemIds[currentWorkIndex]);
                ++sizeOfProcessedWork;
            }

            pair.threadLock.unlock();
        }

        size_t remainder = _systemIds.size() % sizeOfProcessedWork;

        if (remainder != 0)
        {
            if (remainder < amountOfWork)
            {
                QueueLockPair& pair = _threadWorkQueues[0];
                size_t startIndex = _systemIds.size() - remainder;

                pair.threadLock.lock();
                for (size_t i = startIndex; i < _systemIds.size(); i++)
                {
                    if ((_threadAvailabilityMap & 1ULL << i) == 0)
                    {
                        _threadAvailabilityMap ^= 1ULL << i;
                    }

                    pair.systemUpdateIds.push_back(_systemIds[i]);
                }
                pair.threadLock.unlock();
            }
            else
            {
                size_t startIndex = _systemIds.size() - remainder;

                for (size_t i = 0; i < remainder / amountOfWork; i++)
                {
                    size_t offset = startIndex + i;
                    QueueLockPair& pair = _threadWorkQueues[i];

                    pair.threadLock.lock();
                    for (size_t j = 0; j < amountOfWork; j++)
                    {
                        size_t currentWorkIndex = offset + j;

                        if ((_threadAvailabilityMap & 1ULL << i) == 0)
                        {
                            _threadAvailabilityMap ^= 1ULL << i;
                        }

                        pair.systemUpdateIds.push_back(_systemIds[currentWorkIndex]);
                        ++sizeOfProcessedWork;
                    }
                    pair.threadLock.unlock();
                }
            }
        }
        /*
        {
            size_t startIndex = _systemIds.size() - remainder;
            size_t workerIndex = 0;
            for (size_t i = 0; i < remainder; i++)
            {
                size_t offset = startIndex + i;

                if (workerIndex >= _workerThreadCount)
                {
                    workerIndex = 0;
                }

                QueueLockPair& pair = _threadWorkQueues[workerIndex++];

                pair.threadLock.lock();

                if ((_threadAvailabilityMap & 1ULL << i) == 0)
                {
                    _threadAvailabilityMap ^= 1ULL << i;
                }

                pair.systemUpdateIds.push_back(_systemIds[offset]);
                pair.threadLock.unlock();
            }
        }
        */
        while (_threadAvailabilityMap != 0)
        {
            std::this_thread::yield();
        }
    }

    void SystemScheduler::SpinThreads() noexcept
    {
        std::vector<QueueLockPair> vec2(_workerThreadCount);
        _threadWorkQueues.swap(vec2);
        for (size_t i = 0; i < _workerThreadCount; i++)
        {
            _threadShutDownStatus ^= 1ULL << i;
            _threadCache.emplace_back(std::thread([&, i]() { CycleForJob(i); }));
        }
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {

        _currentDelta = delta;

        size_t independentSystemChunkSize = _systemIds.size() / _workerThreadCount;

        size_t workersToAssign = _workerThreadCount > _systemIds.size() ? _systemIds.size() : _workerThreadCount;
        size_t amountOfWork = independentSystemChunkSize > 0 ? independentSystemChunkSize : 1;

        ScheduleUpdateWork(workersToAssign, amountOfWork);
        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());

        _entityCache.ProcessEntityDeletionRequestsFromThreads();
    }

    SystemScheduler::~SystemScheduler() noexcept
    {
        _shouldShutDown = true;

        for (size_t i = 0; i < _threadCache.size(); i++)
        {
            if (_threadCache[i].joinable())
            {
                _threadCache[i].join();
            }
        }
    }
} // namespace NovelRT::Ecs
