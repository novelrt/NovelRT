// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Persistence/Persistence.h>

namespace NovelRT::Persistence
{
    std::unordered_map<std::string, std::unique_ptr<ICustomSerialisationRule>>& Persistable::
        GetSerialisationRules() noexcept
    {
        static std::unordered_map<std::string, std::unique_ptr<ICustomSerialisationRule>> _serialisationRules;
        return _serialisationRules;
    }

    void Persistable::ApplySerialisationRule(const std::string& serialisedName,
                                             gsl::span<const uint8_t> componentData,
                                             gsl::span<uint8_t> writeToData) const
    {
        auto& serialisationRules = GetSerialisationRules();
        auto it = serialisationRules.find(serialisedName);

        if (it == serialisationRules.end())
        {
            return;
        }

        auto newData = it->second->ExecuteSerialiseModification(componentData);
        memcpy(writeToData.data(), newData.data(), writeToData.size());
    }

    void Persistable::ApplyDeserialisationRule(const std::string& serialisedName,
                                               gsl::span<const uint8_t> serialisedData,
                                               gsl::span<uint8_t> writeToData, const std::unordered_map<uuids::uuid, Ecs::EntityId>& uuidToEntityMap) const
    {
        auto& serialisationRules = GetSerialisationRules();
        auto it = serialisationRules.find(serialisedName);

        if (it == serialisationRules.end())
        {
            return;
        }

        auto newData = it->second->ExecuteDeserialiseModification(serialisedData, uuidToEntityMap);
        memcpy(writeToData.data(), newData.data(), writeToData.size());
    }
}
