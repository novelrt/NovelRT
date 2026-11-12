// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <utility>

#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>

namespace NovelRT::Ecs
{
    const EntityAllocator::GenerationAllocationState* EntityAllocator::GetGenerationIfTracked(
        EntityId entity) const noexcept
    {
        auto it = _generationStates.find(entity);

        if (it != _generationStates.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    EntityAllocator::GenerationAllocationState* EntityAllocator::GetGenerationIfTracked(EntityId entity) noexcept
    {
        // TODO: Find a better way to do this than just duplicating code because of the const constraint. - Matt J.
        auto it = _generationStates.find(entity);

        if (it != _generationStates.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    EntityHandle EntityAllocator::Allocate()
    {
        static auto& factory = AtomFactoryDatabase::GetFactory("EntityId");

        if (!_freedEntities.empty())
        {
            EntityId freedEntity = _freedEntities.back();
            _freedEntities.pop_back();

            auto& state = _generationStates.at(freedEntity);

            state.Generation++;
            state.IsCurrentlyAllocated = true;

            return {.Id = freedEntity, .Generation = state.Generation};
        }

        EntityId newEntity = factory.GetNext();
        size_t generation = 0ULL;

        _generationStates.emplace(newEntity,
                                  GenerationAllocationState{.Generation = generation, .IsCurrentlyAllocated = true});

        return {.Id = newEntity, .Generation = generation};
    }

    void EntityAllocator::Free(const EntityHandle& handle)
    {
        auto* generation = GetGenerationIfTracked(handle.Id);

        if (generation == nullptr || !generation->IsCurrentlyAllocated || generation->Generation != handle.Generation)
        {
            return;
        }

        _freedEntities.emplace_back(handle.Id);

        generation->IsCurrentlyAllocated = false;
    }

    EntityHandle EntityAllocator::CreateHandleForAllocated(EntityId entity) const
    {
        const auto* generation = GetGenerationIfTracked(entity);

        if (generation == nullptr || !generation->IsCurrentlyAllocated)
        {
            throw Exceptions::KeyNotFoundException();
        }

        return {.Id = entity, .Generation = generation->Generation};
    }

    bool EntityAllocator::IsValid(const EntityHandle& handle) const noexcept
    {
        const auto* generation = GetGenerationIfTracked(handle.Id);

        return generation != nullptr && generation->IsCurrentlyAllocated && generation->Generation == handle.Generation;
    }
}
