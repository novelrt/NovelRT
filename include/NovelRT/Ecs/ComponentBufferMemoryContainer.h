// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_COMPONENTBUFFERMEMORYCONTAINER_H
#define NOVELRT_ECS_COMPONENTBUFFERMEMORYCONTAINER_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class ComponentBufferMemoryContainer : public std::enable_shared_from_this<ComponentBufferMemoryContainer>
    {
    private:
        SparseSetMemoryContainer _rootSet;
        std::vector<SparseSetMemoryContainer> _updateSets;
        std::vector<uint8_t> _deleteInstructionState;
        size_t _sizeOfDataTypeInBytes;
        std::function<void(void*, const void*, size_t)> _componentUpdateLogic;

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
                memcpy(outputLocation, _data, _sizeOfObject);
            }

            [[nodiscard]] inline const void* GetDataHandle() const noexcept
            {
                return _data;
            }
        };

        ComponentBufferMemoryContainer(size_t poolSize,
                                       const void* deleteInstructionState,
                                       size_t sizeOfDataTypeInBytes,
                                       std::function<void(void*, const void*, size_t)> componentUpdateLogic) noexcept;

        void PrepContainerForFrame(const std::vector<EntityId>& destroyedEntities) noexcept;

        [[nodiscard]] ImmutableDataView GetDeleteInstructionState() const noexcept;

        void PushComponentUpdateInstruction(size_t poolId, EntityId entity, const void* componentData);

        [[nodiscard]] ImmutableDataView GetComponent(EntityId entity) const;
        [[nodiscard]] ImmutableDataView GetComponentUnsafe(EntityId entity) const noexcept;

        [[nodiscard]] bool HasComponent(EntityId entity) const noexcept;

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept;

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator begin() const noexcept;

        [[nodiscard]] SparseSetMemoryContainer::ConstIterator end() const noexcept;
    };
} 

#endif // NOVELRT_ECS_COMPONENTBUFFERMEMORYCONTAINER_H
