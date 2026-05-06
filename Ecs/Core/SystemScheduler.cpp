// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <NovelRT/Maths/Utilities.hpp>

#include <cassert>
#include <functional>

namespace NovelRT::Ecs
{
    SystemScheduler::SystemScheduler(uint32_t maximumThreadCount) noexcept
        : _entityCache(1),
          _componentCache(1),
          _workerThreadCount(maximumThreadCount),
          _ecsArena(std::make_unique<tbb::task_arena>(maximumThreadCount == 0 ? int(tbb::task_arena::automatic)
                                                                              : static_cast<int>(maximumThreadCount))),
          _asyncArena(std::make_unique<tbb::task_arena>(int(tbb::task_arena::automatic))),
          _ecsTasks(std::make_unique<tbb::task_group>()),
          _asyncTasks(std::make_unique<tbb::task_group>()),
          _pendingCompletions(),
          _currentDelta(NovelRT::Timing::TimeFromSeconds(0)),
    {
        _workerThreadCount = _ecsArena->max_concurrency();
        _entityCache = EntityCache(_workerThreadCount);
        _componentCache = ComponentCache(_workerThreadCount);
    }

    SystemScheduler::SystemScheduler(SystemScheduler&& other) noexcept
        : _systemIds(std::move(other._systemIds)),
          _typedSystemCache(std::move(other._typedSystemCache)),
          _systems(std::move(other._systems)),
          _entityCache(std::move(other._entityCache)),
          _componentCache(std::move(other._componentCache)),
          _workerThreadCount(other._workerThreadCount),
          _ecsArena(std::move(other._ecsArena)),
          _asyncArena(std::move(other._asyncArena)),
          _ecsTasks(std::move(other._ecsTasks)),
          _asyncTasks(std::move(other._asyncTasks)),
          _currentDelta(other._currentDelta),
          _pendingCompletions(std::move(other._pendingCompletions))
    {
    }

    SystemScheduler& SystemScheduler::operator=(SystemScheduler&& other) noexcept
    {
        _systemIds = std::move(other._systemIds);
        _typedSystemCache = std::move(other._typedSystemCache);
        _systems = std::move(other._systems);
        _entityCache = std::move(other._entityCache);
        _componentCache = std::move(other._componentCache);
        _workerThreadCount = other._workerThreadCount;
        _ecsArena = std::move(other._ecsArena);
        _asyncArena = std::move(other._asyncArena);
        _ecsTasks = std::move(other._ecsTasks);
        _asyncTasks = std::move(other._asyncTasks);
        _currentDelta = other._currentDelta;
        _pendingCompletions = std::move(other._pendingCompletions);
        return *this;
    }

    void SystemScheduler::RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr) noexcept
    {
        static AtomFactory& systemIdFactory = AtomFactoryDatabase::GetFactory("SystemId");

        Atom id = systemIdFactory.GetNext();
        _systems.emplace(id, systemUpdatePtr);
        _systemIds.emplace_back(id);
    }

    void SystemScheduler::RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem) noexcept
    {
        _typedSystemCache.emplace_back(targetSystem);
        RegisterSystem([targetSystem](auto delta, auto catalogue) { targetSystem->Update(delta, catalogue); });
    }

    void SystemScheduler::ScheduleUpdateWork()
    {
        _ecsArena->execute(
            [&]() 
            {
                std::function<void(Timing::Timestamp, Catalogue)> completion{};
                while (_pendingCompletions.try_pop(completion))
                {
                    _ecsTasks->run(
                        [completion = std::move(completion), this]() 
                        {
                            size_t poolId = static_cast<size_t>(tbb::this_task_arena::current_thread_index());
                            completion(_currentDelta, Catalogue(poolId, *this));
                        });
                }

                for (auto&& systemId : _systemIds)
                {
                    _ecsTasks->run(
                        [&, systemId]() 
                        {
                            size_t poolId = static_cast<size_t>(tbb::this_task_arena::current_thread_index());
                            _systems[systemId](_currentDelta, Catalogue(poolId, *this));
                        });
                }

                _ecsTasks->wait();
            });
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {
        _currentDelta = delta;

        ScheduleUpdateWork();
        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
        _entityCache.ProcessEntityRegistrationRequestsFromThreads();
        _entityCache.ProcessEntityDeletionRequestsFromThreads();
        _entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();
    }

    SystemScheduler::~SystemScheduler() noexcept
    {
        _ecsArena->execute(
            [&]()
            {
                _ecsTasks->wait();
                _asyncTasks->wait();
            });
    }
} // namespace NovelRT::Ecs
