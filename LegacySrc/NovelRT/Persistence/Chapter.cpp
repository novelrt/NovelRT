// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Persistence/Persistence.h>

namespace NovelRT::Persistence
{
    Chapter::Chapter() noexcept : _componentCacheData{}
    {
    }

    Chapter::Chapter(NovelRT::Utilities::Misc::Span<std::shared_ptr<Ecs::ComponentBufferMemoryContainer>>
                         componentCacheData) noexcept
        : _componentCacheData{}
    {
        for (auto&& buffer : componentCacheData)
        {
            _componentCacheData.emplace(buffer->GetSerialisedTypeName(), buffer->GetReadOnlyContainer());
        }
    }

    void Chapter::ToEcsInstance(Ecs::ComponentCache& componentCache, Ecs::EntityCache& entityCache) const
    {
        static AtomFactory& factory = AtomFactoryDatabase::GetFactory("EntityId");
        Ecs::SparseSet<Ecs::EntityId, Ecs::EntityId> localToGlobalEntityMap{};
        auto& registeredGlobalEntities = entityCache.GetRegisteredEntities();
        auto& loadRules = Persistable::GetComponentLoadRules();

        for (Ecs::EntityId entity : registeredGlobalEntities)
        {
            Ecs::EntityId newId = entity;

            while (std::find(registeredGlobalEntities.begin(), registeredGlobalEntities.end(), newId) !=
                   registeredGlobalEntities.end())
            {
                newId = factory.GetNext();
            }

            entityCache.AddEntity(0, newId);
            localToGlobalEntityMap.Insert(entity, newId);
        }

        for (auto&& buffer : componentCache.GetAllComponentBuffers())
        {
            auto& container = _componentCacheData.at(buffer->GetSerialisedTypeName());
            std::vector<uint8_t> tempComponentDataContainer(container.GetSizeOfDataTypeInBytes());

            for (auto&& [entity, it] : container)
            {
                Ecs::EntityId entityId = entity;

                if (localToGlobalEntityMap.ContainsKey(entityId))
                {
                    entityId = localToGlobalEntityMap[entityId];
                }

                it.CopyFromLocation(tempComponentDataContainer.data());

                auto loadRuleIt = loadRules.find(buffer->GetSerialisedTypeName());

                if (loadRuleIt != loadRules.end())
                {
                    loadRuleIt->second->ExecuteComponentLoadModification(localToGlobalEntityMap,
                                                                         tempComponentDataContainer.data());
                }

                buffer->PushComponentUpdateInstruction(0, entityId, tempComponentDataContainer.data());
            }
        }
    }

    Chapter Chapter::FromEcsInstance(const Ecs::ComponentCache& componentCache) noexcept
    {
        auto buffers = componentCache.GetAllComponentBuffers(); // This is required due to Span requirements
        return Chapter(buffers);
    }

    ResourceManagement::BinaryPackage Chapter::ToFileData() const noexcept
    {
        ResourceManagement::BinaryPackage package{};

        package.data = std::vector<uint8_t>{};

        for (auto&& dataPair : _componentCacheData)
        {
            size_t amountOfEntities = dataPair.second.Length();
            size_t oldLength = package.data.size();
            auto& rules = GetSerialisationRules();

            auto entityMetadata = ResourceManagement::BinaryMemberMetadata{dataPair.first + "_entities",
                                                                           ResourceManagement::BinaryDataType::Binary,
                                                                           oldLength,
                                                                           sizeof(Ecs::EntityId),
                                                                           amountOfEntities,
                                                                           0};
            package.memberMetadata.emplace_back(entityMetadata);

            auto componentMetadata = ResourceManagement::BinaryMemberMetadata{
                dataPair.first + "_components",
                ResourceManagement::BinaryDataType::Binary,
                oldLength + (entityMetadata.length * entityMetadata.sizeOfTypeInBytes),
                dataPair.second.GetSizeOfDataTypeInBytes(),
                amountOfEntities,
                0};

            auto it = rules.find(dataPair.first);

            if (it != rules.end())
            {
                componentMetadata.sizeOfSerialisedDataInBytes = it->second->GetSerialisedSize();
            }

            package.memberMetadata.emplace_back(componentMetadata);

            if (componentMetadata.sizeOfSerialisedDataInBytes != 0)
            {
                package.data.resize(package.data.size() + (entityMetadata.length * entityMetadata.sizeOfTypeInBytes) +
                                    (componentMetadata.length * componentMetadata.sizeOfSerialisedDataInBytes));
            }
            else
            {
                package.data.resize(package.data.size() + (entityMetadata.length * entityMetadata.sizeOfTypeInBytes) +
                                    (componentMetadata.length * componentMetadata.sizeOfTypeInBytes));
            }

            size_t sizeOfComponentType = dataPair.second.GetSizeOfDataTypeInBytes();

            auto entityPtr = reinterpret_cast<Ecs::EntityId*>(package.data.data() + oldLength);
            auto componentPtr =
                package.data.data() + oldLength + (entityMetadata.length * entityMetadata.sizeOfTypeInBytes);

            for (auto&& [entity, dataView] : dataPair.second)
            {
                const size_t sizeOfEntityId = sizeof(Ecs::EntityId);
                NovelRT::Utilities::Memory::Copy(entityPtr, sizeOfEntityId, &entity, sizeOfEntityId);

                size_t componentJumpValue = sizeOfComponentType;
                if (componentMetadata.sizeOfSerialisedDataInBytes == 0)
                {
                    dataView.CopyFromLocation(componentPtr);
                }
                else
                {
                    componentJumpValue = componentMetadata.sizeOfSerialisedDataInBytes;
                    ApplySerialisationRule(dataPair.first,
                                           NovelRT::Utilities::Misc::Span<const uint8_t>(
                                               reinterpret_cast<const uint8_t*>(dataView.GetDataHandle()),
                                               dataPair.second.GetSizeOfDataTypeInBytes()),
                                           NovelRT::Utilities::Misc::Span<uint8_t>(
                                               componentPtr, componentMetadata.sizeOfSerialisedDataInBytes));
                }

                entityPtr++;
                componentPtr += componentJumpValue;
            }
        }

        return package;
    }

    void Chapter::LoadFileData(const ResourceManagement::BinaryPackage& data)
    {
        _componentCacheData.clear();

        struct PointerSpan
        {
            const Ecs::EntityId* entities = nullptr;
            const uint8_t* components = nullptr;
            size_t entityCount = 0;
            size_t sizeOfComponentInBytes = 0;
            size_t sizeOfSerialisedDataInBytes = 0;
        };

        std::map<std::string, PointerSpan> tempMap{};

        for (auto&& metadata : data.memberMetadata)
        {
            std::istringstream iss(metadata.name);
            std::vector<std::string> splitName{};
            std::string item;

            while (std::getline(iss, item, '_'))
            {
                splitName.emplace_back(item);
            }

            auto& bufferRootName = splitName[0];
            auto& bufferPartName = splitName[1];

            auto it = tempMap.find(bufferRootName);

            if (it == tempMap.end())
            {
                tempMap[bufferRootName] = PointerSpan{};
                it = tempMap.find(bufferRootName);
            }

            auto& span = it->second;

            if (bufferPartName == "entities")
            {
                span.entities = reinterpret_cast<const Ecs::EntityId*>(&data.data[metadata.location]);
                span.entityCount = metadata.length;
            }
            else if (bufferPartName == "components")
            {
                span.components = &data.data[metadata.location];
                span.sizeOfComponentInBytes = metadata.sizeOfTypeInBytes;
                span.sizeOfSerialisedDataInBytes = metadata.sizeOfSerialisedDataInBytes;
            }
            else
            {
                throw std::runtime_error("Invalid binary package member for Chapter");
            }
        }

        std::map<std::string, Ecs::SparseSetMemoryContainer> newBufferState{};
        auto& serialisationRules = GetSerialisationRules();

        for (auto&& pair : tempMap)
        {
            Ecs::SparseSetMemoryContainer container(pair.second.sizeOfComponentInBytes);

            if (serialisationRules.find(pair.first) != serialisationRules.end())
            {
                std::vector<uint8_t> newBufferData{};
                newBufferData.resize(pair.second.sizeOfComponentInBytes * pair.second.entityCount);

                auto bufferDataPtr = newBufferData.data();
                auto serialisedDataPtr = pair.second.components;

                for (size_t i = 0; i < pair.second.entityCount; i++)
                {
                    ApplyDeserialisationRule(
                        pair.first,
                        NovelRT::Utilities::Misc::Span<const uint8_t>(serialisedDataPtr,
                                                                      pair.second.sizeOfSerialisedDataInBytes),
                        NovelRT::Utilities::Misc::Span<uint8_t>(reinterpret_cast<uint8_t*>(bufferDataPtr),
                                                                pair.second.sizeOfComponentInBytes));
                    bufferDataPtr += pair.second.sizeOfComponentInBytes;
                    serialisedDataPtr += pair.second.sizeOfSerialisedDataInBytes;
                }

                container.ResetAndWriteDenseData(reinterpret_cast<const size_t*>(pair.second.entities),
                                                 pair.second.entityCount, newBufferData.data());
            }
            else
            {
                container.ResetAndWriteDenseData(reinterpret_cast<const size_t*>(pair.second.entities),
                                                 pair.second.entityCount, pair.second.components);
            }

            newBufferState.emplace(pair.first, container);
        }

        _componentCacheData = newBufferState;
    }
}
