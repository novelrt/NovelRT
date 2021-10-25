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

        // in case the previous call doesn't work
        if (_workerThreadCount == 0)
        {
            _workerThreadCount = DEFAULT_BLIND_THREAD_LIMIT;
        }

        _threadAvailabilityMap = (1ULL << _workerThreadCount) - 1;

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
          _threadAvailabilityMap((1ULL << other._workerThreadCount) - 1),
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
        _threadWorkItem = std::move(other._threadWorkItem);
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

    void SystemScheduler::RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem) noexcept
    {
        _typedSystemCache.emplace_back(targetSystem);
        RegisterSystem([targetSystem](auto delta, auto catalogue) { targetSystem->Update(delta, catalogue); });
    }

    bool SystemScheduler::JobAvailable(size_t poolId) const noexcept
    {
        return (_threadAvailabilityMap & (1ULL << poolId)) == 0;
    }

    void SystemScheduler::CycleForJob(size_t poolId)
    {
        while (true)
        {
            while (!JobAvailable(poolId))
            {
                std::this_thread::yield();
            }

            Atom workItem = _threadWorkItem[poolId];

            if (workItem == std::numeric_limits<Atom>::max())
            {
                return;
            }

            _systems[workItem](_currentDelta, Catalogue(poolId, _componentCache, _entityCache));

            assert(((_threadAvailabilityMap & (1ULL << poolId)) == 0) && "Thread marked as available while working!");
            _threadAvailabilityMap ^= (1ULL << poolId);
            assert(((_threadAvailabilityMap & (1ULL << poolId)) == (1ULL << poolId)) &&
                   "Thread marked as busy while available!");
        }
    }

    void SystemScheduler::ScheduleUpdateWork()
    {
        uint64_t threadAvailabilityMap = _threadAvailabilityMap;
        assert((threadAvailabilityMap == ((1ULL << _workerThreadCount) - 1)) &&
               "Some threads are busy while new work is attempted to be scheduled!");
        for (auto&& systemId : _systemIds)
        {
            uint64_t workerIndex;

            while ((workerIndex = NovelRT::Maths::Utilities::LeadingZeroCount64(_threadAvailabilityMap)) == 64)
            {
                std::this_thread::yield();
            }

            workerIndex = 63 - workerIndex;

            assert((workerIndex <= (_workerThreadCount)) &&
                   "Returned worker index does not exist! Index out of range.");

            _threadWorkItem[workerIndex] = systemId;

            assert(((_threadAvailabilityMap & (1ULL << workerIndex)) == (1ULL << workerIndex)) &&
                   "Thread marked as busy while available!");
            _threadAvailabilityMap ^= (1ULL << workerIndex);
            assert(((_threadAvailabilityMap & (1ULL << workerIndex)) == 0) &&
                   "Thread marked as available while working!");
        }

        while (_threadAvailabilityMap != threadAvailabilityMap)
        {
            std::this_thread::yield();
        }
    }

    void SystemScheduler::SpinThreads() noexcept
    {
        _shouldShutDown = false;
        std::vector<Atom> vec2(_workerThreadCount);
        _threadWorkItem.swap(vec2);

        for (size_t i = 0; i < _workerThreadCount; i++)
        {
            _threadCache.emplace_back(std::thread([&, i]() { CycleForJob(i); }));
        }

        _threadsAreSpinning = true;
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {

        _currentDelta = delta;

        ScheduleUpdateWork();
        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
        _entityCache.ProcessEntityDeletionRequestsFromThreads();
    }

    void SystemScheduler::ShutDown() noexcept
    {
        assert((_threadAvailabilityMap == ((1ULL << _workerThreadCount) - 1)) &&
               "Work was scheduled while the SystemScheduler is shutting down!");
        for (auto&& workItem : _threadWorkItem)
        {
            workItem = std::numeric_limits<Atom>::max();
        }

        _threadAvailabilityMap = 0;

        for (auto&& i : _threadCache)
        {
            if (i.joinable())
            {
                i.join();
            }
        }

        _threadCache.clear();
        _threadWorkItem.clear();
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
