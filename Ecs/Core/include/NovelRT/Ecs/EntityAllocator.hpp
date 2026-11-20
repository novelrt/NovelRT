#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <map>
#include <memory>
#include <vector>

#include <tbb/mutex.h>

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
        std::unique_ptr<tbb::mutex> _accessMutex;

        [[nodiscard]] const GenerationAllocationState* GetGenerationIfTracked(EntityId entity) const noexcept;
        [[nodiscard]] GenerationAllocationState* GetGenerationIfTracked(EntityId entity) noexcept;

    public:
        EntityAllocator();

        /**
         * @brief Allocates a brand new entity and begins internal tracking.
         *
         * @detail If a previously freed entity is available, the entity
         * will be recycled here.
         *
         * @exception std::bad_alloc if it fails to allocate. This should not be occuring unless
         * the computer is out of memory.
         *
         * @return an EntityHandle that is guaranteed to be valid.
         */
        [[nodiscard]] EntityHandle Allocate();

        /**
         * @brief Frees the EntityId associated with this EntityHandle, if valid.
         *
         * @detail If the provided EntityHandle is invalid, it will simply abort silently.
         *
         * @exception std::bad_alloc if it fails to reorganise allocated memory during the Free attempt.
         * This should not be occuring unless the computer ran out of memory.
         */
        void Free(const EntityHandle& handle);

        /**
         * @brief Creates a new valid EntityHandle for a given EntityId.
         *
         * @exception Exceptions::KeyNotFoundException if the EntityId is not
         * allocated by this allocator.
         *
         * @return an EntityHandle that is guaranteed to be valid.
         */
        [[nodiscard]] EntityHandle CreateHandleForAllocated(EntityId entity) const;

        /**
         * @brief Checks if a given EntityHandle is currently valid or not.
         *
         * @detail The EntityAllocator currently will recycle generations if it loops from SIZE_MAX to 0ULL.
         * If you have handles that you are still storing that were previously invalid, they will become valid
         * again should the relevant generation be reached.
         *
         * @return true if it is valid, false if it isn't.
         */
        [[nodiscard]] bool IsValid(const EntityHandle& handle) const noexcept;
    };
}
