// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/UnsafeComponentView.h>
#include <utility>

namespace NovelRT::Ecs
{
    UnsafeComponentView::UnsafeComponentView(size_t poolId,
                                             std::shared_ptr<ComponentBufferMemoryContainer> memoryContainer) noexcept
        : _poolId(poolId), _memoryContainer(std::move(memoryContainer))
    {
    }

    void UnsafeComponentView::PushComponentUpdateInstruction(EntityId entity, void* instructionState)
    {
        _memoryContainer->PushComponentUpdateInstruction(_poolId, entity, instructionState);
    }

    void UnsafeComponentView::RemoveComponent(EntityId entity)
    {
        _memoryContainer->PushComponentUpdateInstruction(_poolId, entity, _memoryContainer->GetDeleteInstructionState().GetDataHandle());
    }

    ComponentBufferMemoryContainer::ImmutableDataView UnsafeComponentView::GetComponent(EntityId entity) const
    {
        return _memoryContainer->GetComponent(entity);
    }

    ComponentBufferMemoryContainer::ImmutableDataView UnsafeComponentView::GetComponentUnsafe(
        EntityId entity) const noexcept
    {
        return _memoryContainer->GetComponentUnsafe(entity);
    }

    size_t UnsafeComponentView::GetImmutableDataLength() const noexcept
    {
        return _memoryContainer->GetImmutableDataLength();
    }

    // clang-format off

    SparseSetMemoryContainer::ConstIterator UnsafeComponentView::begin() const noexcept
    {
        return _memoryContainer->begin();
    }

    SparseSetMemoryContainer::ConstIterator UnsafeComponentView::end() const noexcept
    {
        return _memoryContainer->end();
    }

    // clang-format on
} // namespace NovelRT::Ecs