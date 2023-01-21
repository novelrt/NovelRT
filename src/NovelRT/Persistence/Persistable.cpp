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

    std::unordered_map<std::string, std::unique_ptr<ICustomComponentLoadRule>>& Persistable::
        GetComponentLoadRules() noexcept
    {
        static std::unordered_map<std::string, std::unique_ptr<ICustomComponentLoadRule>> _componentLoadRules;
        return _componentLoadRules;
    }

    void Persistable::ApplySerialisationRule(const std::string& serialisedName,
                                             NovelRT::Utilities::Misc::Span<const uint8_t> componentData,
                                             NovelRT::Utilities::Misc::Span<uint8_t> writeToData) const
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
                                               NovelRT::Utilities::Misc::Span<const uint8_t> serialisedData,
                                               NovelRT::Utilities::Misc::Span<uint8_t> writeToData) const
    {
        auto& serialisationRules = GetSerialisationRules();
        auto it = serialisationRules.find(serialisedName);

        if (it == serialisationRules.end())
        {
            return;
        }

        auto newData = it->second->ExecuteDeserialiseModification(serialisedData);
        memcpy(writeToData.data(), newData.data(), writeToData.size());
    }

    // TODO: Rework this at a later date.
    void Persistable::LoadDefaultRules(std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> renderingSystem) noexcept
    {
        auto& serialisationRules = GetSerialisationRules();

        serialisationRules.emplace("NovelRT::Ecs::Graphics::RenderComponent",
                                   std::unique_ptr<ICustomSerialisationRule>(
                                       new Graphics::RenderingComponentPersistenceRule(std::move(renderingSystem))));
    }
}
