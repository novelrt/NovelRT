// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT/Ecs/SystemScheduler.h>

namespace NovelRT::Ecs
{
    SystemScheduler::SystemScheduler(uint32_t maximumThreadCount) noexcept : _entityCache(1),
                                                                             _componentCache(1),
                                                                             _workerThreadCount(maximumThreadCount),
                                                                             _currentDelta(0),
                                                                             _threadAvailabilityMap(0),
                                                                             _threadShutDownStatus(0),
                                                                             _shouldShutDown(false),
                                                                             _ecsDataBufferIndex(0)
    {
        if (_workerThreadCount != 0)
        {
            return;
        }

        _workerThreadCount = std::thread::hardware_concurrency() - 1;

        //in case the previous call doesn't work
        if (_workerThreadCount == 0)
        {
            _workerThreadCount = DEFAULT_BLIND_THREAD_LIMIT;
        }

        _entityCache = EntityCache(_workerThreadCount);
        _componentCache = ComponentCache(_workerThreadCount);
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

                std::this_thread::yield();
            }

            bool firstIteration = true;

            while (true)
            {
                QueueLockPair &pair = _threadWorkQueues[poolId];
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
        int32_t sizeOfProcessedWork = 0;

        for (size_t i = 0; i < workersToAssign; i++)
        {
            size_t offset = i * amountOfWork;
            QueueLockPair &pair = _threadWorkQueues[i];

            _threadAvailabilityMap ^= 1ULL << i;

            pair.threadLock.lock();

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
                QueueLockPair &pair = _threadWorkQueues[0];
                size_t startIndex = (_systemIds.size() - 1) - remainder;

                pair.threadLock.lock();
                for (size_t i = startIndex; i < _systemIds.size(); i++)
                {
                    pair.systemUpdateIds.push_back(_systemIds[i]);
                }
                pair.threadLock.unlock();
            }
            else if (remainder > amountOfWork)
            {
                size_t startIndex = (_systemIds.size() - 1) - remainder;

                for (size_t i = 0; i < remainder / amountOfWork; i++)
                {
                    size_t offset = startIndex + (i * amountOfWork);
                    QueueLockPair &pair = _threadWorkQueues[i];

                    pair.threadLock.lock();

                    for (size_t j = 0; j < amountOfWork; j++)
                    {
                        size_t currentWorkIndex = offset + j;
                        pair.systemUpdateIds.push_back(_systemIds[currentWorkIndex]);
                        ++sizeOfProcessedWork;
                    }

                    pair.threadLock.unlock();
                }
            }
        }

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
        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
        
        _currentDelta = delta;

        size_t independentSystemChunkSize = _systemIds.size() / _workerThreadCount;

        size_t workersToAssign = _workerThreadCount > _systemIds.size() ? _systemIds.size() : _workerThreadCount;
        size_t amountOfWork = independentSystemChunkSize > 0 ? independentSystemChunkSize : 1;

        ScheduleUpdateWork(workersToAssign, amountOfWork);

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
