// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT/Ecs/SystemScheduler.h>
#include <iostream>

namespace NovelRT::Ecs
{
    SystemScheduler::SystemScheduler(uint32_t maximumThreadCount) :
    _maximumThreadCount(maximumThreadCount),
    _currentDelta(0),
    _threadAvailabilityMap(0),
    _threadShutDownStatus(0),
    _shouldShutDown(false)
    {
        if (_maximumThreadCount != 0)
        {
            return;
        }

        _maximumThreadCount = std::thread::hardware_concurrency() - 1;
        //in case the previous call doesn't work
        if (_maximumThreadCount == 0)
        {
            _maximumThreadCount = DEFAULT_BLIND_THREAD_LIMIT;
        }

        std::cerr << "THREAD COUNT LOG: " << _maximumThreadCount << std::endl;
    }

    bool SystemScheduler::JobAvailable(size_t poolId) noexcept
    {
        QueueLockPair& pair = _threadWorkQueues[poolId];
        pair.threadLock.lock();
        if (pair.systemIds.size() > 0)
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
            _threadAvailabilityMap.fetch_xor(1ULL << poolId);
            while (!JobAvailable(poolId))
            {
                if (_shouldShutDown)
                {
                    _threadShutDownStatus.fetch_xor(1ULL << poolId);
                    return;
                }

                std::this_thread::yield();
            }

            _threadAvailabilityMap.fetch_xor(1ULL << poolId); //this runs AFTER the while check in the main thread

            QueueLockPair& pair = _threadWorkQueues[poolId];
            Atom workItem = pair.systemIds[0];
            pair.systemIds.erase(pair.systemIds.begin());

            pair.threadLock.unlock();

            _systems[workItem].systemPtr(_currentDelta);
        }
    }

    void SystemScheduler::SpinThreads() noexcept
    {
        std::vector<QueueLockPair> vec2(_maximumThreadCount);
        _threadWorkQueues.swap(vec2);
        for (size_t i = 0; i < _maximumThreadCount; i++)
        {
            _threadShutDownStatus.fetch_xor(1ULL << i);
            _threadAvailabilityMap.fetch_xor(1ULL << i);
            _threadCache.emplace_back(std::thread([&, i](){CycleForJob(i);}));
        }
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {
        _currentDelta = delta;

        size_t independentSystemChunkSize = _systemIds.size() / _maximumThreadCount;

        size_t workersToAssign = _maximumThreadCount > _systemIds.size() ? _systemIds.size() : _maximumThreadCount;
        size_t amountOfWork = independentSystemChunkSize > 0 ? independentSystemChunkSize : 1;

        int32_t sizeOfProcessedWork = 0;

        for (size_t i = 0; i < workersToAssign; i++)
        {
            size_t offset = i * amountOfWork;
            QueueLockPair& pair = _threadWorkQueues[i];

            pair.threadLock.lock();

            for (size_t j = 0; j < amountOfWork; j++)
            {
                size_t currentWorkIndex = offset + j;
                pair.systemIds.push_back(_systemIds[currentWorkIndex]);
                ++sizeOfProcessedWork;
            }

            pair.threadLock.unlock();
        }

        size_t remainder = _systemIds.size() % sizeOfProcessedWork;

        if(remainder != 0)
        {
            if (remainder < amountOfWork)
            {
                QueueLockPair& pair = _threadWorkQueues[0];
                size_t startIndex = (_systemIds.size() - 1) - remainder;

                pair.threadLock.lock();
                for (size_t i = startIndex; i < _systemIds.size(); i++)
                {
                    pair.systemIds.push_back(_systemIds[i]);
                }
                pair.threadLock.unlock();
            }
            else if (remainder > amountOfWork)
            {
                size_t startIndex = (_systemIds.size() - 1) - remainder;

                for (size_t i = 0; i < remainder / amountOfWork; i++)
                {
                    size_t offset = startIndex + (i * amountOfWork);
                    QueueLockPair& pair = _threadWorkQueues[i];

                    pair.threadLock.lock();

                    for (size_t j = 0; j < amountOfWork; j++)
                    {
                        size_t currentWorkIndex = offset + j;
                        pair.systemIds.push_back(_systemIds[currentWorkIndex]);
                        ++sizeOfProcessedWork;
                    }

                    pair.threadLock.unlock();
                }
            }
        }

        while (_threadAvailabilityMap.load() != 0)
        {
            std::this_thread::yield();
        }

    }

    SystemScheduler::~SystemScheduler() noexcept
    {
        _shouldShutDown = true;

      for (size_t i = 0; i < _threadCache.size(); i++) {
        if (_threadCache[i].joinable()) {
          _threadCache[i].join();
          }
      }
    }
}
