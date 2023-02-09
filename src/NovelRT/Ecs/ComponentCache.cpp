// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
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
        const void* deleteInstructionState,
        const std::function<void(void*, const void*, size_t)>& componentUpdateLogic,
        const std::function<bool(void*, void*)>& compareComponents,
        const std::string& serialisedTypeName) const
    {
        return std::make_shared<ComponentBufferMemoryContainer>(_poolSize, deleteInstructionState, sizeOfDataType,
                                                                componentUpdateLogic, compareComponents, serialisedTypeName);
    }

    ComponentTypeId ComponentCache::RegisterComponentTypeUnsafe(
        size_t sizeOfDataType,
        const void* deleteInstructionState,
        const std::function<void(void*, const void*, size_t)>& componentUpdateLogic,
        const std::function<bool(void*, void*)>& compareComponents,
        const std::string& serialisedTypeName)
    {
        static AtomFactory& _componentTypeIdFactory = AtomFactoryDatabase::GetFactory("ComponentTypeId");

        ComponentTypeId returnId = _componentTypeIdFactory.GetNext();
        std::shared_ptr<ComponentBufferMemoryContainer> ptr =
            CreateContainer(sizeOfDataType, deleteInstructionState, componentUpdateLogic, compareComponents, serialisedTypeName);
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
