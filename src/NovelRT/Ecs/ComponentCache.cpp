// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.h>
#include <utility>

namespace NovelRT::Ecs
{
    ComponentCache::ComponentCache(size_t poolSize) noexcept
        : _componentMap(
              std::unordered_map<ComponentTypeId, std::shared_ptr<ComponentBufferMemoryContainer>, AtomHashFunction>{}),
          _poolSize(poolSize),
          _bufferPrepEvent(Utilities::Event<const std::vector<EntityId>&>())
    {
    }

    std::shared_ptr<ComponentBufferMemoryContainer> ComponentCache::CreateContainer(
        size_t sizeOfDataType,
        void* deleteInstructionState,
        const std::function<void(SparseSetMemoryContainer::ByteIteratorView,
                                 SparseSetMemoryContainer::ByteIteratorView,
                                 size_t)>& componentUpdateLogic) const
    {
        return std::make_shared<ComponentBufferMemoryContainer>(_poolSize, deleteInstructionState, sizeOfDataType,
                                                                componentUpdateLogic);
    }

    ComponentTypeId ComponentCache::RegisterComponentTypeUnsafe(
        size_t sizeOfDataType,
        void* deleteInstructionState,
        const std::function<void(SparseSetMemoryContainer::ByteIteratorView,
                           SparseSetMemoryContainer::ByteIteratorView,
                           size_t)>& componentUpdateLogic)
    {
        ComponentTypeId returnId = Atom::getNextComponentTypeId();
        std::shared_ptr<ComponentBufferMemoryContainer> ptr =
            CreateContainer(sizeOfDataType, deleteInstructionState, componentUpdateLogic);
        _bufferPrepEvent += [ptr](auto vec) { ptr->PrepContainerForFrame(vec); };
        _componentMap.emplace(returnId, ptr);
        return returnId;
    }

    std::shared_ptr<ComponentBufferMemoryContainer> ComponentCache::GetComponentBufferById(ComponentTypeId id) const
    {
        return _componentMap.at(id);
    }

    void ComponentCache::PrepAllBuffersForNextFrame(const std::vector<EntityId>& entitiesToDelete) noexcept
    {
        _bufferPrepEvent(entitiesToDelete);
    }
} // namespace NovelRT::Ecs