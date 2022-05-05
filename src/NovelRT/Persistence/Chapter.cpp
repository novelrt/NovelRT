// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Persistence/Persistence.h>
#include "NovelRT/Persistence/Chapter.h"

namespace NovelRT::Persistence
{
    Chapter::Chapter(gsl::span<std::shared_ptr<Ecs::ComponentBufferMemoryContainer>> componentCacheData) noexcept
        : _componentCacheData{}
    {
        for (auto&& buffer : componentCacheData)
        {
            _componentCacheData.emplace(buffer->GetSerialisedTypeName(), buffer->GetReadOnlyContainer());
        }
    }

    void Chapter::ToEcsInstance(Ecs::ComponentCache& componentCache) const
    {
        static AtomFactory& factory = AtomFactoryDatabase::GetFactory("EntityId");
        for (auto&& buffer : componentCache.GetAllComponentBuffers())
        {
            auto& container = _componentCacheData.at(buffer->GetSerialisedTypeName());
            auto& rootSet = buffer->GetReadOnlyContainer();

            for (auto&& [entity, it] : container)
            {
                Ecs::EntityId entityId = entity;

                if (rootSet.ContainsKey(entity))
                {
                    entityId = factory.GetNext();
                }

                buffer->PushComponentUpdateInstruction(0, entityId, it.GetDataHandle());
            }
        }
    }

    Chapter Chapter::FromEcsInstance(const Ecs::ComponentCache& componentCache) noexcept
    {
        auto buffers = componentCache.GetAllComponentBuffers(); // This is required due to Span requirements
        return Chapter(buffers);
    }

    std::map<std::string, IPersistable::ComponentBufferInformation> Chapter::ToFileData() const noexcept
    {
        std::map<std::string, ComponentBufferInformation> data{};

        for (auto&& dataPair : _componentCacheData)
        {
            ComponentBufferInformation info{};
            info.amountOfEntities = dataPair.second.Length();
            info.entityComponentData = std::vector<uint8_t>{};
            info.entityComponentData.reserve((sizeof(Ecs::EntityId) * info.amountOfEntities) + (dataPair.second.GetSizeOfDataTypeInBytes() * info.amountOfEntities));
            info.sizeOfComponentType = dataPair.second.GetSizeOfDataTypeInBytes();

            auto entityPtr = reinterpret_cast<Ecs::EntityId*>(info.entityComponentData.data());
            auto componentPtr = &info.entityComponentData[sizeof(Ecs::EntityId) * info.amountOfEntities];

            for (auto&& [entity, dataView] : dataPair.second)
            {
                std::memcpy(entityPtr, &entity, sizeof(Ecs::EntityId));
                dataView.CopyFromLocation(componentPtr);

                entityPtr++;
                componentPtr += info.sizeOfComponentType;
            }

            data.emplace(dataPair.first, info);
        }

        return data;
    }

    void Chapter::LoadFileData(const std::map<std::string, ComponentBufferInformation>& data) noexcept
    {
        _componentCacheData.clear();

        for (auto&& pair : data)
        {
            Ecs::SparseSetMemoryContainer container(pair.second.sizeOfComponentType);

            auto entityPtr = reinterpret_cast<const Ecs::EntityId*>(pair.second.entityComponentData.data());
            auto componentPtr = &pair.second.entityComponentData[sizeof(Ecs::EntityId) * pair.second.amountOfEntities];

            for (size_t index = 0; index < pair.second.amountOfEntities; index++)
            {
                container.Insert(entityPtr[index], &componentPtr[index * pair.second.sizeOfComponentType]);
            }

            _componentCacheData.emplace(pair.first, container);
        }
    }
}