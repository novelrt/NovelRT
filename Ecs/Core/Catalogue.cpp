// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <NovelRT/Ecs/UnsafeComponentView.hpp>

#include <algorithm>
#include <utility>

namespace NovelRT::Ecs
{
    Catalogue::Catalogue(size_t poolId, SystemScheduler& scheduler) noexcept
        : _poolId(poolId),
          _componentCache(scheduler.GetComponentCache()),
          _entityCache(scheduler.GetEntityCache()),
          _scheduler(scheduler),
          _createdEntitiesThisFrame(std::vector<EntityId>{})
    {
    }

    EntityId Catalogue::CreateEntity() noexcept
    {
        static AtomFactory& _entityIdFactory = AtomFactoryDatabase::GetFactory("EntityId");
        auto& knownEntities = _entityCache.GetRegisteredEntities();

        EntityId returnId = _entityIdFactory.GetNext();

        while (std::find(knownEntities.begin(), knownEntities.end(), returnId) != knownEntities.end())
        {
            returnId = _entityIdFactory.GetNext();
        }

        _entityCache.AddEntity(_poolId, returnId);
        _createdEntitiesThisFrame.push_back(returnId);
        return returnId;
    }

    void Catalogue::DeleteEntity(EntityId entity) noexcept
    {
        if (std::find(_createdEntitiesThisFrame.begin(), _createdEntitiesThisFrame.end(), entity) !=
            _createdEntitiesThisFrame.end())
        {
            return;
        }

        _entityCache.RemoveEntity(_poolId, entity);
    }

    UnsafeComponentView Catalogue::GetComponentViewById(ComponentTypeId componentTypeId)
    {
        return UnsafeComponentView(_poolId, _componentCache.GetComponentBufferById(componentTypeId));
    }

    SystemId Catalogue::ScheduleSystemJob(std::function<bool(Timing::Timestamp, Catalogue)> jobFnPtr)
    {
        return _scheduler.ScheduleSystemJob(std::move(jobFnPtr));
    }

    void Catalogue::CancelSystemJob(SystemId jobId)
    {
        _scheduler.CancelSystemJob(jobId);
    }
} // namespace NovelRT::Ecs
