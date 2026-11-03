// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/SparseSetMemoryContainer.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>

#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Memory.hpp>

#include <stdexcept>
#include <utility>

namespace NovelRT::Ecs
{
    ComponentBufferMemoryContainer::ComponentBufferMemoryContainer(
        size_t poolSize,
        const std::byte* deleteInstructionState,
        size_t sizeOfDataTypeInBytes,
        std::function<bool(const void*, const void*)> componentComparatorLogic,
        std::optional<std::function<void(void*, const void*, size_t)>> componentUpdateLogic,
        std::optional<std::function<void(void*, const void*, size_t)>> componentAssignmentLogic,
        std::string serialisedTypeName)
        : _rootSet(SparseSetMemoryContainer(sizeOfDataTypeInBytes)),
          _updateSets{},
          _assignmentFlags(poolSize),
          _deleteInstructionState(sizeOfDataTypeInBytes),
          _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes),
          _componentUpdateLogic(std::move(componentUpdateLogic)),
          _componentAssignmentLogic(std::move(componentAssignmentLogic)),
          _componentComparatorLogic(std::move(componentComparatorLogic)),
          _serialisedTypeName(std::move(serialisedTypeName))
    {
        if (!_componentUpdateLogic.has_value() && !_componentAssignmentLogic.has_value())
        {
            throw std::invalid_argument(
                "A component buffer must have at least one method for updating component data.");
        }

        NovelRT::Utilities::Memory::Copy(
            NovelRT::Utilities::Span<const std::byte>{deleteInstructionState, _sizeOfDataTypeInBytes},
            NovelRT::Utilities::Span<std::byte>{_deleteInstructionState.data(), _sizeOfDataTypeInBytes});

        for (size_t i = 0; i < poolSize; i++)
        {
            _updateSets.emplace_back(sizeOfDataTypeInBytes);
        }
    }

    void ComponentBufferMemoryContainer::PrepContainerForFrame(const std::vector<EntityId>& destroyedEntities) noexcept
    {
        for (size_t poolId = 0; poolId < _updateSets.size(); ++poolId)
        {
            auto& updateSet = _updateSets[poolId];
            auto& flags = _assignmentFlags[poolId];
            size_t denseIndex = 0;

            for (auto [entity, component] : updateSet)
            {
                const bool isAssignment = flags[denseIndex++] != 0;
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
                    if (isAssignment)
                    {
                        _componentAssignmentLogic.value()(_rootSet[entity].GetDataHandle(), component.GetDataHandle(),
                                                          _sizeOfDataTypeInBytes);
                    }
                    else
                    {
                        _componentUpdateLogic.value()(_rootSet[entity].GetDataHandle(), component.GetDataHandle(),
                                                      _sizeOfDataTypeInBytes);
                    }
                }
            }

            updateSet.Clear();
            flags.clear();
        }

        for (EntityId entity : destroyedEntities)
        {
            unused(_rootSet.TryRemove(entity));
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
        if (!_componentUpdateLogic.has_value())
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to apply an update merge instruction when no logic was supplied.");
        }

        auto& set = _updateSets.at(poolId);
        auto& flags = _assignmentFlags.at(poolId);
        if (set.ContainsKey(entity))
        {
            _componentUpdateLogic.value()(set[entity].GetDataHandle(), componentData, _sizeOfDataTypeInBytes);
            // A merge into a pending assignment remains an assignment at frame resolution.
            return;
        }

        flags.push_back(0);
        try
        {
            set.Insert(entity, componentData);
        }
        catch (...)
        {
            flags.pop_back();
            throw;
        }
    }

    void ComponentBufferMemoryContainer::PushComponentAssignmentInstruction(size_t poolId,
                                                                            EntityId entity,
                                                                            const void* componentData)
    {
        if (!_componentAssignmentLogic.has_value())
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to apply an assignment instruction when no logic was supplied.");
        }

        auto& set = _updateSets.at(poolId);
        auto& flags = _assignmentFlags.at(poolId);
        if (set.ContainsKey(entity))
        {
            _componentAssignmentLogic.value()(set[entity].GetDataHandle(), componentData, _sizeOfDataTypeInBytes);
            flags[set.GetDenseIndexUnsafe(entity)] = 1;
            return;
        }

        flags.push_back(1);
        try
        {
            set.Insert(entity, componentData);
        }
        catch (...)
        {
            flags.pop_back();
            throw;
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
