// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_ICUSTOMSERIALISATIONRULE_H
#define NOVELRT_PERSISTENCE_ICUSTOMSERIALISATIONRULE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class ICustomSerialisationRule
    {
    public:
        virtual ~ICustomSerialisationRule() = default;

        [[nodiscard]] virtual size_t GetSerialisedSize() const noexcept = 0;
        [[nodiscard]] virtual std::vector<uint8_t> ExecuteSerialiseModification(
            gsl::span<const uint8_t> component) const noexcept = 0;
        [[nodiscard]] virtual std::vector<uint8_t> ExecuteDeserialiseModification(
            gsl::span<const uint8_t> component, const std::unordered_map<uuids::uuid, Ecs::EntityId>& uuidsToEntitiesMap) const noexcept = 0;
    };
}
#endif // NOVELRT_PERSISTENCE_ICUSTOMSERIALISATIONRULE_H
