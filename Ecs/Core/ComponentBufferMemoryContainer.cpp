// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/SparseSetMemoryContainer.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>

#include <NovelRT/Utilities/Memory.hpp>

#include <utility>

namespace NovelRT::Ecs
{
    ComponentBufferMemoryContainer::ComponentBufferMemoryContainer(
        size_t poolSize,
        const std::byte* deleteInstructionState,
        size_t sizeOfDataTypeInBytes,
        std::function<void(void*, const void*, size_t)> componentUpdateLogic,
        std::function<bool(const void*, const void*)> componentComparatorLogic,
        const std::string& serialisedTypeName) noexcept
        : _rootSet(SparseSetMemoryContainer(sizeOfDataTypeInBytes)),
          _updateSets(std::vector<SparseSetMemoryContainer>{}),
          _deleteInstructionState(sizeOfDataTypeInBytes),
          _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes),
          _componentUpdateLogic(std::move(componentUpdateLogic)),
          _componentComparatorLogic(std::move(componentComparatorLogic)),
          _serialisedTypeName(serialisedTypeName)
    {
        NovelRT::Utilities::Memory::Copy(
            NovelRT::Utilities::Span{deleteInstructionState, _sizeOfDataTypeInBytes},
            NovelRT::Utilities::Span{_deleteInstructionState.data(), _sizeOfDataTypeInBytes});

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
                if (_componentComparatorLogic(component.GetDataHandle(), _deleteInstructionState.data()))
                {
                    _rootSet.TryRemove(entity);
                }
                else if (!_rootSet.ContainsKey(entity))
                {
                    _rootSet.Insert(entity, component.GetDataHandle());
                }
                else
                {
                    _componentUpdateLogic(_rootSet[entity].GetDataHandle(), component.GetDataHandle(),
                                          _sizeOfDataTypeInBytes);
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
        auto& set = _updateSets.at(poolId);
        if (!set.TryInsert(entity, componentData))
        {
            _componentUpdateLogic(set[entity].GetDataHandle(), componentData, _sizeOfDataTypeInBytes);
        }
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
