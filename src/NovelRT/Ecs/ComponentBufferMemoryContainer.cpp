// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBufferMemoryContainer.h>
#include <utility>

namespace NovelRT::Ecs
{
    ComponentBufferMemoryContainer::ComponentBufferMemoryContainer(
        size_t poolSize,
        const void* deleteInstructionState,
        size_t sizeOfDataTypeInBytes,
        std::function<void(SparseSetMemoryContainer::ByteIteratorView,
                           SparseSetMemoryContainer::ByteIteratorView,
                           size_t)> componentUpdateLogic) noexcept
        : _rootSet(SparseSetMemoryContainer(sizeOfDataTypeInBytes)),
          _updateSets(std::vector<SparseSetMemoryContainer>{}),
          _deleteInstructionState(std::vector<std::byte>(sizeOfDataTypeInBytes)),
          _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes),
          _componentUpdateLogic(std::move(componentUpdateLogic))
    {
        std::memcpy(_deleteInstructionState.data(), deleteInstructionState, _sizeOfDataTypeInBytes);
        for (size_t i = 0; i < poolSize; i++)
        {
            _updateSets.emplace_back(sizeOfDataTypeInBytes);
        }
    }

    void ComponentBufferMemoryContainer::PrepContainerForFrame(const std::vector<EntityId>& destroyedEntities) noexcept
    {
        for (auto&& updateSet : _updateSets)
        {
            for (auto [entity, component] : updateSet)
            {
                if (std::memcmp(component.GetDataHandle(), _deleteInstructionState.data(), _sizeOfDataTypeInBytes) == 0)
                {
                    _rootSet.TryRemove(entity);
                }
                else if (!_rootSet.ContainsKey(entity))
                {
                    _rootSet.Insert(entity, component.GetDataHandle());
                }
                else
                {
                    _componentUpdateLogic(_rootSet[entity], component, _sizeOfDataTypeInBytes);
                }
            }
            updateSet.Clear();
        }

        for (EntityId i : destroyedEntities)
        {
            _rootSet.TryRemove(i);
        }
    }

    ComponentBufferMemoryContainer::ImmutableDataView ComponentBufferMemoryContainer::GetDeleteInstructionState()
        const noexcept
    {
        return ComponentBufferMemoryContainer::ImmutableDataView(
            reinterpret_cast<const void*>(_deleteInstructionState.data()), _sizeOfDataTypeInBytes);
    }

    void ComponentBufferMemoryContainer::PushComponentUpdateInstruction(size_t poolId,
                                                                        EntityId entity,
                                                                        const void* componentData)
    {
        _updateSets[poolId].Insert(entity, componentData);
    }

    ComponentBufferMemoryContainer::ImmutableDataView ComponentBufferMemoryContainer::GetComponent(
        EntityId entity) const
    {
        if (!_rootSet.ContainsKey(entity))
        {
            throw Exceptions::KeyNotFoundException();
        }

        return ComponentBufferMemoryContainer::ImmutableDataView(_rootSet[entity].GetDataHandle(), entity);
    }

    ComponentBufferMemoryContainer::ImmutableDataView ComponentBufferMemoryContainer::GetComponentUnsafe(
        EntityId entity) const noexcept
    {
        return ComponentBufferMemoryContainer::ImmutableDataView(_rootSet[entity].GetDataHandle(), entity);
    }

    bool ComponentBufferMemoryContainer::HasComponent(EntityId entity) const noexcept
    {
        return _rootSet.ContainsKey(entity);
    }

    size_t ComponentBufferMemoryContainer::GetImmutableDataLength() const noexcept
    {
        return _rootSet.Length();
    }

    SparseSetMemoryContainer::ConstIterator ComponentBufferMemoryContainer::begin() const noexcept
    {
        return _rootSet.cbegin();
    }

    SparseSetMemoryContainer::ConstIterator ComponentBufferMemoryContainer::end() const noexcept
    {
        return _rootSet.cend();
    }
} // namespace NovelRT::Ecs
