// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <NovelRT/Ecs/UnsafeComponentView.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>

#include <utility>

namespace NovelRT::Ecs
{
    Catalogue::Catalogue(size_t poolId, SystemScheduler& scheduler) noexcept
        : _poolId(poolId),
          _componentCache(scheduler.GetComponentCache()),
          _entityCache(scheduler.GetEntityCache()),
          _scheduler(scheduler),
          _entityAllocator(scheduler.GetEntityAllocator())
    {
    }

    EntityHandle Catalogue::CreateEntity()
    {
        EntityHandle newHandle = _entityAllocator.Allocate();
        _entityCache.AddEntity(_poolId, newHandle);

        return newHandle;
    }

    void Catalogue::DeleteEntity(EntityId entity)
    {
        DeleteEntity(_entityAllocator.CreateHandleForAllocated(entity));
    }

    void Catalogue::DeleteEntity(const EntityHandle& entity)
    {
        if (!_entityAllocator.IsValid(entity))
        {
            throw Exceptions::KeyNotFoundException();
        }

        _entityCache.RemoveEntity(_poolId, entity);
    }

    UnsafeComponentView Catalogue::GetComponentViewById(ComponentTypeId componentTypeId)
    {
        return {_poolId, _componentCache.GetComponentBufferById(componentTypeId)};
    }

    SystemId Catalogue::ScheduleSystemJob(
        std::function<bool(Timing::Timestamp, Timing::Timestamp::duration, Catalogue)> jobFnPtr)
    {
        return _scheduler.ScheduleSystemJob(std::move(jobFnPtr));
    }

    void Catalogue::CancelSystemJob(SystemId jobId) noexcept
    {
        _scheduler.CancelSystemJob(jobId);
    }
} // namespace NovelRT::Ecs
