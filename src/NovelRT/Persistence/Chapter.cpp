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

    IPersistable::BinaryPackage Chapter::ToFileData() const noexcept
    {
        BinaryPackage package{};

        package.data = std::vector<uint8_t>{};

        for (auto&& dataPair : _componentCacheData)
        {
            size_t amountOfEntities = dataPair.second.Length();
            size_t oldLength = package.data.size();
            package.memberMetadata.emplace_back(BinaryMemberMetadata { dataPair.first, BinaryDataType::Binary, oldLength, ( sizeof(Ecs::EntityId) * amountOfEntities) + (dataPair.second.GetSizeOfDataTypeInBytes() * amountOfEntities) });
            package.data.resize(package.data.size() + (sizeof(Ecs::EntityId) * amountOfEntities) + (dataPair.second.GetSizeOfDataTypeInBytes() * amountOfEntities));
            size_t sizeOfComponentType = dataPair.second.GetSizeOfDataTypeInBytes();

            auto entityPtr = reinterpret_cast<Ecs::EntityId*>(package.data.data() + oldLength);
            auto componentPtr = package.data.data() + oldLength + (sizeof(Ecs::EntityId) * amountOfEntities);

            for (auto&& [entity, dataView] : dataPair.second)
            {
                std::memcpy(entityPtr, &entity, sizeof(Ecs::EntityId));
                dataView.CopyFromLocation(componentPtr);

                entityPtr++;
                componentPtr += sizeOfComponentType;
            }
        }

        return package;
    }

    void Chapter::LoadFileData(const BinaryPackage& data) noexcept
    {
        _componentCacheData.clear();
    }
}