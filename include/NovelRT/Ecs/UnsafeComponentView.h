// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UNSAFECOMPONENTVIEW_H
#define NOVELRT_UNSAFECOMPONENTVIEW_H

#include "ComponentBufferMemoryContainer.h"
#include <memory>

namespace NovelRT::Ecs
{
    class UnsafeComponentView
    {
    private:
        size_t _poolId;
        std::shared_ptr<ComponentBufferMemoryContainer> _memoryContainer;

    public:
        UnsafeComponentView(size_t poolId, std::shared_ptr<ComponentBufferMemoryContainer> memoryContainer) noexcept;

        void PushComponentUpdateInstruction(EntityId entity, void* instructionState);

        void RemoveComponent(EntityId entity);

        [[nodiscard]] ComponentBufferMemoryContainer::ImmutableDataView GetComponent(EntityId entity) const;

        [[nodiscard]] ComponentBufferMemoryContainer::ImmutableDataView GetComponentUnsafe(EntityId entity) const noexcept;

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept;

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator begin() const noexcept;

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator end() const noexcept;
    };
}

#endif // !NOVELRT_UNSAFECOMPONENTVIEW_H
