#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <map>
#include <optional>
#include <vector>

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/EntityHandle.hpp>
#include <NovelRT/Utilities/Atom.hpp>

namespace NovelRT::Ecs
{
    class EntityAllocator
    {
    private:
        struct GenerationAllocationState
        {
            size_t Generation;
            bool IsCurrentlyAllocated;
        };

        std::map<EntityId, GenerationAllocationState> _generationStates;
        std::vector<EntityId> _freedEntities;

        [[nodiscard]] const GenerationAllocationState* GetGenerationIfTracked(EntityId entity) const noexcept;
        [[nodiscard]] GenerationAllocationState* GetGenerationIfTracked(EntityId entity) noexcept;

    public:
        [[nodiscard]] EntityHandle Allocate();

        void Free(const EntityHandle& handle);

        [[nodiscard]] EntityHandle CreateHandleForAllocated(EntityId entity) const;

        [[nodiscard]] bool IsValid(const EntityHandle& handle) const noexcept;
    };
}
