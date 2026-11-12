// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Exceptions/KeyNotFoundException.hpp"
#include <NovelRT/Ecs/EntityAllocator.hpp>

namespace NovelRT::Ecs
{
    std::optional<size_t> EntityAllocator::GetGenerationIfTracked(EntityId entity) const noexcept
    {
        auto it = _generationState.find(entity);

        if (it != _generationState.end())
        {
            return it->second;
        }

        return std::nullopt;
    }

    EntityHandle EntityAllocator::Allocate()
    {
        static auto factory = AtomFactoryDatabase::GetFactory("EntityId");

        if (!_freedEntities.empty())
        {
            EntityId freedEntity = _freedEntities.back();
            _freedEntities.pop_back();

            const size_t newGeneration = ++_generationState.at(freedEntity);

            return {.Id = freedEntity, .Generation = newGeneration};
        }

        EntityId newEntity = factory.GetNext();
        size_t generation = 0ULL;

        _generationState.emplace(newEntity, generation);

        return {.Id = newEntity, .Generation = generation};
    }

    void EntityAllocator::Free(const EntityHandle& handle)
    {
        auto generation = GetGenerationIfTracked(handle.Id);

        if (!generation.has_value() || generation.value() != handle.Generation)
        {
            return;
        }

        _freedEntities.emplace_back(handle.Id);
    }

    EntityHandle EntityAllocator::CreateHandleForAllocated(EntityId entity) const
    {
        auto generation = GetGenerationIfTracked(entity);

        if (!generation.has_value())
        {
            throw Exceptions::KeyNotFoundException();
        }

        return {.Id = entity, .Generation = generation.value()};
    }

    bool EntityAllocator::IsValid(const EntityHandle& handle) const noexcept
    {
        auto generation = GetGenerationIfTracked(handle.Id);

        return generation.has_value() && generation.value() == handle.Generation;
    }
}
