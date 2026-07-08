// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Timing/Timestamp.hpp"
#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <NovelRT/Maths/Utilities.hpp>
#include <NovelRT/Utilities/Macros.hpp>

#include <atomic>
#include <cassert>
#include <functional>
#include <unordered_map>
#include <utility>

namespace NovelRT::Ecs
{
    SystemId SystemScheduler::ScheduleSystemJob(std::function<bool(Timing::Timestamp, Catalogue)> jobFnPtr)
    {
        static AtomFactory& systemIdFactory = AtomFactoryDatabase::GetFactory("SystemId");
        SystemId id = systemIdFactory.GetNext();

        _systemJobs.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                            std::forward_as_tuple(std::move(jobFnPtr)));

        return id;
    }

    void SystemScheduler::CancelSystemJob(SystemId jobId)
    {
        _jobCancellations.emplace(jobId);
    }

    void SystemScheduler::RebuildSystemDependencyTreeLayers()
    {
        // Special casing terminal systems e.g. the render orchestrator with this. - Matt J.
        for (auto&& id : _terminalSystemIds)
        {
            std::vector<SystemId> allOtherSystems{};
            for (auto&& otherId : _systemIds)
            {
                if (otherId != id && _terminalSystemIds.find(otherId) == _terminalSystemIds.end())
                {
                    allOtherSystems.emplace_back(otherId);
                }
            }

            _systemDependencies.at(id) = std::move(allOtherSystems);
        }

        // This is based on topologic sort with kahn's algorithm. I hope I implemented this right. I am tired. - Matt J.

        std::unordered_map<SystemId, size_t> inDegree{};
        std::unordered_map<SystemId, std::vector<SystemId>> dependents{};

        for (auto&& id : _systemIds)
        {
            inDegree.try_emplace(id, 0);
            dependents.try_emplace(id, std::vector<SystemId>{});
        }

        for (auto&& [id, dependencies] : _systemDependencies)
        {
            inDegree.at(id) = dependencies.size();

            for (auto&& dep : dependencies)
            {
                dependents.at(dep).emplace_back(id);
            }
        }

        _schedulingLayers.clear();

        while (true)
        {
            std::vector<SystemId> currentLayer{};

            for (auto&& [id, degree] : inDegree)
            {
                if (degree == 0)
                {
                    currentLayer.emplace_back(id);
                }
            }

            if (currentLayer.empty())
            {
                break;
            }

            for (auto&& id : currentLayer)
            {
                inDegree.erase(id);

                for (auto&& dependent : dependents.at(id))
                {
                    // just want to decrement this value here. Unused macro is for explicitness. - Matt J.
                    unused(inDegree.at(dependent)--);
                }
            }

            _schedulingLayers.emplace_back(std::move(currentLayer));
        }

        if (!inDegree.empty())
        {
            throw Exceptions::InvalidOperationException("A cycle was detected in the system dependency graph. Please "
                                                        "check your system dependencies for circular references.");
        }
    }

    SystemId SystemScheduler::RegisterSystemInternalNoTreeRebuild(
        std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr,
        std::span<const SystemId> dependencies)
    {
        for (SystemId dep : dependencies)
        {
            if (std::find(_systemIds.begin(), _systemIds.end(), dep) == _systemIds.end())
            {
                throw std::invalid_argument("A provided dependency ID does not match any registered system. "
                                            "Ensure all dependency systems are registered before being referenced.");
            }
        }

        static AtomFactory& systemIdFactory = AtomFactoryDatabase::GetFactory("SystemId");

        SystemId id = systemIdFactory.GetNext();
        _systems.emplace(id, systemUpdatePtr);
        _systemIds.emplace_back(id);
        _systemDependencies.emplace(id, std::vector<SystemId>(dependencies.begin(), dependencies.end()));

        return id;
    }

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
          _systemJobs(),
          _jobCancellations(),
          _currentDelta(NovelRT::Timing::TimeFromSeconds(0)),
          _hasExecutedAtLeastOnce(false)
    {
        _workerThreadCount = static_cast<uint32_t>(_ecsArena->max_concurrency());
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
          _pendingCompletions(std::move(other._pendingCompletions)),
          _systemJobs(std::move(other._systemJobs)),
          _jobCancellations(std::move(other._jobCancellations)),
          _currentDelta(other._currentDelta),
          _hasExecutedAtLeastOnce(other._hasExecutedAtLeastOnce)
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
        _pendingCompletions = std::move(other._pendingCompletions);
        _systemJobs = std::move(other._systemJobs);
        _jobCancellations = std::move(other._jobCancellations);
        _currentDelta = other._currentDelta;
        _hasExecutedAtLeastOnce = other._hasExecutedAtLeastOnce;

        return *this;
    }

    SystemId SystemScheduler::RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr,
                                             std::span<const SystemId> dependencies)
    {
        if (_hasExecutedAtLeastOnce)
        {
            throw Exceptions::InvalidOperationException(
                "Systems cannot be registered after the first iteration has executed. Register all systems during "
                "initialisation.");
        }

        SystemId id = RegisterSystemInternalNoTreeRebuild(systemUpdatePtr, dependencies);
        RebuildSystemDependencyTreeLayers();

        return id;
    }

    SystemId SystemScheduler::RegisterSystem(std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr)
    {
        return RegisterSystem(systemUpdatePtr, {});
    }

    SystemId SystemScheduler::RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem,
                                             std::span<const SystemId> dependencies)
    {
        if (std::find(_typedSystemCache.begin(), _typedSystemCache.end(), targetSystem) != _typedSystemCache.end())
        {
            throw std::invalid_argument(
                "The provided system pointer has already been registered. Each system may only be registered once.");
        }

        _typedSystemCache.emplace_back(targetSystem);

        return RegisterSystem([targetSystem](auto delta, auto catalogue) { targetSystem->Update(delta, catalogue); },
                              dependencies);
    }

    SystemId SystemScheduler::RegisterSystem(std::shared_ptr<IEcsSystem> targetSystem)
    {
        return RegisterSystem(targetSystem, {});
    }

    SystemId SystemScheduler::RegisterSystemDependsOnAll(
        std::function<void(Timing::Timestamp, Catalogue)> systemUpdatePtr)
    {
        if (_hasExecutedAtLeastOnce)
        {
            throw Exceptions::InvalidOperationException(
                "Systems cannot be registered after the first iteration has executed. Register all systems during "
                "initialisation.");
        }

        SystemId id = RegisterSystemInternalNoTreeRebuild(systemUpdatePtr, {});

        _terminalSystemIds.emplace(id);
        RebuildSystemDependencyTreeLayers();

        return id;
    }

    SystemId SystemScheduler::RegisterSystemDependsOnAll(std::shared_ptr<IEcsSystem> targetSystem)
    {
        if (std::find(_typedSystemCache.begin(), _typedSystemCache.end(), targetSystem) != _typedSystemCache.end())
        {
            throw std::invalid_argument(
                "The provided system pointer has already been registered. Each system may only be registered once.");
        }

        _typedSystemCache.emplace_back(targetSystem);

        return RegisterSystemDependsOnAll([targetSystem](auto delta, auto catalogue)
                                          { targetSystem->Update(delta, catalogue); });
    }

    void SystemScheduler::ScheduleUpdateWork()
    {
        _ecsArena->execute(
            [&]()
            {
                for (auto& layer : _schedulingLayers)
                {
                    std::function<void(Timing::Timestamp, Catalogue)> completion{};

                    bool hadCompletions = false;

                    while (_pendingCompletions.try_pop(completion))
                    {
                        hadCompletions = true;
                        _ecsTasks->run(
                            [completion = std::move(completion), this]()
                            {
                                size_t poolId = static_cast<size_t>(tbb::this_task_arena::current_thread_index());
                                completion(_currentDelta, Catalogue(poolId, *this));
                            });
                    }

                    _ecsTasks->wait();

                    if (hadCompletions)
                    {
                        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
                        _entityCache.ProcessEntityRegistrationRequestsFromThreads();
                        _entityCache.ProcessEntityDeletionRequestsFromThreads();
                        _entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();
                    }

                    for (auto& [_, systemJob] : _systemJobs)
                    {
                        unused(_);

                        _ecsTasks->run(
                            [&systemJob, this]()
                            {
                                auto poolId = static_cast<size_t>(tbb::this_task_arena::current_thread_index());
                                systemJob.isDone = systemJob.jobFnPtr(_currentDelta, Catalogue(poolId, *this));
                            });
                    }

                    _ecsTasks->wait();

                    bool hadTombstones = false;

                    // a bit ugly, but couldn't think of a better way to do it right now - Matt J.
                    for (auto it = _systemJobs.begin(); it != _systemJobs.end();)
                    {
                        if (it->second.isDone)
                        {
                            hadTombstones = true;
                            it = _systemJobs.unsafe_erase(it);
                        }
                        else
                        {
                            it++;
                        }
                    }

                    SystemId cancellationId = 0ULL;

                    while (_jobCancellations.try_pop(cancellationId))
                    {
                        _systemJobs.unsafe_erase(cancellationId);
                    }

                    if (hadTombstones)
                    {
                        _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
                        _entityCache.ProcessEntityRegistrationRequestsFromThreads();
                        _entityCache.ProcessEntityDeletionRequestsFromThreads();
                        _entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();
                    }

                    for (SystemId systemId : layer)
                    {
                        _ecsTasks->run(
                            [&, systemId]()
                            {
                                auto poolId = static_cast<size_t>(tbb::this_task_arena::current_thread_index());
                                _systems[systemId](_currentDelta, Catalogue(poolId, *this));
                            });
                    }

                    _ecsTasks->wait();

                    _componentCache.PrepAllBuffersForNextFrame(_entityCache.GetEntitiesToRemoveThisFrame());
                    _entityCache.ProcessEntityRegistrationRequestsFromThreads();
                    _entityCache.ProcessEntityDeletionRequestsFromThreads();
                    _entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();
                }
            });
    }

    void SystemScheduler::ExecuteIteration(Timing::Timestamp delta)
    {
        _hasExecutedAtLeastOnce = true;
        _currentDelta = delta;
        ScheduleUpdateWork();
    }

    SystemScheduler::~SystemScheduler() noexcept
    {
        _ecsArena->execute([&]() { _ecsTasks->wait(); });

        _asyncArena->execute([&]() { _asyncTasks->wait(); });
    }
} // namespace NovelRT::Ecs
