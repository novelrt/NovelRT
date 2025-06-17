#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace NovelRT::Ecs
{
    class SparseSetMemoryContainer;

    class ComponentBufferMemoryContainer : public std::enable_shared_from_this<ComponentBufferMemoryContainer>
    {
    private:
        SparseSetMemoryContainer _rootSet;
        std::vector<SparseSetMemoryContainer> _updateSets;
        std::vector<std::byte> _deleteInstructionState;
        size_t _sizeOfDataTypeInBytes;
        std::function<void(void*, const void*, size_t)> _componentUpdateLogic;
        std::function<bool(const void*, const void*)> _componentComparatorLogic;
        std::string _serialisedTypeName;

    public:
        class ImmutableDataView
        {
        private:
            const void* _data;
            size_t _sizeOfObject;

        public:
            explicit ImmutableDataView(const void* data, size_t sizeOfObject) noexcept
                : _data(data), _sizeOfObject(sizeOfObject)
            {
            }

            inline void CopyDataFromLocation(void* outputLocation) const noexcept
            {
                NovelRT::Utilities::Memory::Copy(outputLocation, _sizeOfObject, _data, _sizeOfObject);
            }

            [[nodiscard]] inline const void* GetDataHandle() const noexcept
            {
                return _data;
            }
        };

        ComponentBufferMemoryContainer(size_t poolSize,
                                       const std::byte* deleteInstructionState,
                                       size_t sizeOfDataTypeInBytes,
                                       std::function<void(void*, const void*, size_t)> componentUpdateLogic,
                                       std::function<bool(const void*, const void*)> componentComparatorLogic,
                                       const std::string& serialisedTypeName) noexcept;

        void PrepContainerForFrame(const std::vector<EntityId>& destroyedEntities) noexcept;

        [[nodiscard]] ImmutableDataView GetDeleteInstructionState() const noexcept;

        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, const void* componentData);

        [[nodiscard]] ImmutableDataView GetComponent(EntityId entity) const;
        [[nodiscard]] ImmutableDataView GetComponentUnsafe(EntityId entity) const noexcept;

        [[nodiscard]] bool HasComponent(EntityId entity) const noexcept;

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept;

        [[nodiscard]] inline const std::string& GetSerialisedTypeName() const noexcept
        {
            return _serialisedTypeName;
        }

        [[nodiscard]] inline const SparseSetMemoryContainer& GetReadOnlyContainer() const noexcept
        {
            return _rootSet;
        }

        [[nodiscard]] inline size_t GetSizeOfDataTypeInBytes() const noexcept
        {
            return _sizeOfDataTypeInBytes;
        }

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator begin() const noexcept;

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator end() const noexcept;
    };
}
