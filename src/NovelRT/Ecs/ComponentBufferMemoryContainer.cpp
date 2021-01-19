// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT/Ecs/ComponentBufferMemoryContainer.h>

namespace NovelRT::Ecs
{
    ComponentBufferMemoryContainer::ComponentBufferMemoryContainer(size_t poolSize, void* deleteInstructionState, size_t sizeOfDataTypeInBytes) noexcept :
    _rootSet(SparseSetMemoryContainer(sizeOfDataTypeInBytes)),
    _updateSets(std::vector<SparseSetMemoryContainer>{}),
    _deleteInstructionState(std::vector<std::byte>(sizeOfDataTypeInBytes)),
    _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes)
    {
        std::memcpy(_deleteInstructionState.data(), deleteInstructionState, _sizeOfDataTypeInBytes);
        for (int i = 0; i < poolSize; ++i)
        {
            _updateSets.emplace_back(sizeOfDataTypeInBytes);
        }
    }

    void ComponentBufferMemoryContainer::PrepContainerForFrame(const std::vector<EntityId> &destroyedEntities, std::function<void(SparseSetMemoryContainer::ByteIteratorView, SparseSetMemoryContainer::ByteIteratorView, size_t)> componentUpdateLogic) noexcept
    {
        for (auto&& updateSet : _updateSets)
        {
            for (auto [entity, component] : updateSet)
            {
                if (std::memcmp(component.GetDataHandle(), _deleteInstructionState.data(), _sizeOfDataTypeInBytes) == 0)
                {
                    _rootSet.TryRemove(entity);
                }
                else if(!_rootSet.ContainsKey(entity))
                {
                    _rootSet.Insert(entity, component.GetDataHandle());
                }
                else
                {
                    componentUpdateLogic(_rootSet[entity], component, _sizeOfDataTypeInBytes);
                }
            }
            updateSet.Clear();
        }

        for (EntityId i : destroyedEntities)
        {
            _rootSet.TryRemove(i);
        }
    }

    ComponentBufferMemoryContainer::ImmutableDataView ComponentBufferMemoryContainer::GetDeleteInstructionState() const noexcept
    {
        return ComponentBufferMemoryContainer::ImmutableDataView(reinterpret_cast<const void*>(_deleteInstructionState.data()), _sizeOfDataTypeInBytes);
    }

    void ComponentBufferMemoryContainer::PushComponentUpdateInstruction(size_t poolId, EntityId entity, void* componentData)
    {
        _updateSets[poolId].Insert(entity, componentData);
    }

    ComponentBufferMemoryContainer::ImmutableDataView ComponentBufferMemoryContainer::GetComponent(EntityId entity) const
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

    // clang-format off

    SparseSetMemoryContainer::ConstIterator ComponentBufferMemoryContainer::begin() const noexcept
    {
        return _rootSet.cbegin();
    }

    SparseSetMemoryContainer::ConstIterator ComponentBufferMemoryContainer::end() const noexcept
    {
        return _rootSet.cend();
    }

    // clang-format on
}

